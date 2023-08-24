/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:16:48 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/24 10:57:30 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(void)
{
	char	*str;
	char	**str1;
	pid_t	pid;

	init_signals();
	str = generate_entry();
	while (str && (ft_strncmp(str, "exit", ft_strlen(str)) != 0
			|| ft_strlen(str) == 0))
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
