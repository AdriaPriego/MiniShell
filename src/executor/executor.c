/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:45:12 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/11 15:42:50 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_childs(t_pipe *data)
{
	int	i;

	close(data->fd[0]);
	close(data->fd[1]);
	i = 0;
	while (i < data->n_cmds)
	{
		waitpid(data->pid[i], &data->exit_status, 0);
		i++;
	}
	free (data->pid);
	if (WIFEXITED(data->exit_status))
		ft_printf("Exit: %i\n", (WEXITSTATUS(data->exit_status)));
}

void	new_pipe(t_cmd *commands, t_pipe *data, char **envp)
{
	int		exit_code;
	char	*path;

	manage_redirections(commands, data);
	close(data->fd[0]);
	close(data->fd[1]);
	exit_code = search_path(commands->args[0], envp, &path);
	if (exit_code == CMD_NOT_FOUND)
		error_exit(data, exit_code, commands->args[0], MSSG_CMD_NOT_FOUND);
	else if (exit_code != 0)
		perror_exit(data, exit_code, commands->args[0]);
	execve(path, commands->args, envp);
	perror_exit(data, EXIT_FAILURE, "Execve");
}

int	execute_commands(t_cmd *commands, char **envp)
{
	t_pipe	data;
	int		i;

	if (!commands)
		return (0);
	if (init_data(&data, commands) == 1)
		return (1);
	if (pipe(data.fd) == -1)
		return (perror_return(&data, EXIT_FAILURE, "Pipe"));
	i = 0;
	while (commands)
	{
		data.pid[i] = fork();
		if (data.pid[i] == -1)
			return (perror_return(&data, EXIT_FAILURE, "Fork"));
		else if (data.pid[i] == 0)
			new_pipe(commands, &data, envp);
		commands = commands->next;
		i++;
	}
	wait_childs(&data);
	return (0);
}
