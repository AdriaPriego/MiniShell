/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:02:01 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/11 01:13:41 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_cmd *commands)
{
	int	i;

	i = 0;
	while (commands)
	{
		i++;
		commands = commands->next;
	}
	return (i);
}

int	init_data(t_pipe *data, t_cmd *commands)
{
	int	i;

	data->n_cmds = count_commands(commands);
	data->pid  = malloc(sizeof(pid_t) * data->n_cmds);
	if (!data->pid)
		return (1);
	return (0);
}

void	error_exit(int exit_code, char *name, char *error) //MAKE SURE TO FREE PIDS BEFORE EXIT
{
	ft_printf_fd(STDERR_FILENO, "minishell: ");
	ft_printf_fd(STDERR_FILENO, "%s: %s\n", name, error);
	exit(exit_code);
}

void	perror_exit(int exit_code, char *error) //MAKE SURE TO FREE PIDS BEFORE EXIT
{
	ft_printf_fd(STDERR_FILENO, "minishell: ");
	perror(error);
	exit(exit_code);
}
