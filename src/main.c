/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:16:48 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/14 12:20:02 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **envp)
{
	char	**env;

	(void)av;
	if (ac != 1)
	{
		ft_printf_fd(STDERR_FILENO, MSSG_INVALID_ARGS);
		return (1);
	}
	env = ft_dup_matrix(envp);
	if (!env)
	{
		ft_printf_fd(STDERR_FILENO, MSSG_MEMORY_ERROR);
		return (0);
	}
	init_signals();
	generate_terminal(env);
	ft_matrix_free(env);
	return (0);
}
