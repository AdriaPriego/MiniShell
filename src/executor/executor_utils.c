/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:02:01 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/11 13:29:46 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_data(t_pipe *data, t_cmd *commands)
{
	int	i;

	data->n_cmds = parser_lstsize(commands);
	data->pid = malloc(sizeof(pid_t) * data->n_cmds);
	if (!data->pid)
		return (1);
	return (0);
}

void	error_exit(t_pipe *data, int exit_code, char *name, char *error)
{
	free(data->pid);
	ft_printf_fd(STDERR_FILENO, "minishell: ");
	ft_printf_fd(STDERR_FILENO, "%s: %s\n", name, error);
	exit(exit_code);
}

void	perror_exit(t_pipe *data, int exit_code, char *error)
{
	free(data->pid);
	ft_printf_fd(STDERR_FILENO, "minishell: ");
	perror(error);
	exit(exit_code);
}

int	perror_return(t_pipe *data, int return_code, char *error)
{
	free(data->pid);
	ft_printf_fd(STDERR_FILENO, "minishell: ");
	perror(error);
	return (return_code);
}
