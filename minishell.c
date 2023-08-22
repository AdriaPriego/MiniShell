/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:16:48 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/22 18:01:28 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	if (signum == SIGQUIT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(void)
{
	char	*str;
	char	**str1;
	pid_t	pid;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	str = generate_entry();
	rl_on_new_line();
	rl_redisplay();
	while (str && ft_strncmp(str, "exit", ft_strlen(str)) != 0)
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
	free(str);
	return (0);
}
