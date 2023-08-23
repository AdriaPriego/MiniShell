/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:16:48 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/23 18:45:05 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	test_exist(char *str)
{
	if (!str)
		return (0);
	return (1);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	if (signum == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

int	main(void)
{
	char	*str;
	char	**str1;
	pid_t	pid;

	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	str = generate_entry();
	while (str && (ft_strncmp(str, "exit", ft_strlen(str)) != 0 || ft_strlen(str) == 0))
	{
		add_history(str);
		str1 = generate(str);
		pid = fork();
		if (pid == 0)
			execve("/bin/bash", str1, NULL);
		wait(0);
		ft_free_matrix((const char **)str1, 3);
		str = generate_entry();
	}
	if (!str || !ft_strncmp(str, "exit", ft_strlen(str)))
		ft_printf("exit\n");
	free(str);
	return (0);
}
