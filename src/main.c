/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:16:48 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/18 18:08:40 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **envp)
{
	t_env	*enve;

	(void)av;
	if (ac != 1)
	{
		ft_printf_fd(STDERR_FILENO, MSSG_INVALID_ARGS);
		return (1);
	}
	enve = ft_dup_matrix_env(envp);
	if (!enve)
	{
		ft_printf_fd(STDERR_FILENO, MSSG_MEMORY_ERROR);
		return (0);
	}
	rl_catch_signals = 0;
	init_signals(DEFAULT);
	generate_terminal(enve);
	return (0);
}
