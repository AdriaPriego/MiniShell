/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:02:01 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/14 20:36:55 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_original_stds(int *in, int *out)
{
	*in = dup(STDIN_FILENO);
	*out = dup(STDOUT_FILENO);
}

int	init_data(t_pipe *data, t_cmd *commands)
{
	data->n_cmds = parser_lstsize(commands);
	data->fd[0] = -1;
	data->fd[1] = -1;
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
