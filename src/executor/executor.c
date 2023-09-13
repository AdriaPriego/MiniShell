/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:45:12 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/13 18:20:31 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_childs(t_pipe *data)
{
	int	i;
	int	status;

	dup2(data->dup_stdin, STDIN_FILENO);
	dup2(data->dup_stdout, STDOUT_FILENO);
	i = 0;
	while (i < data->n_cmds)
	{
		waitpid(data->pid[i], &status, 0);
		i++;
	}
	free(data->pid);
	/* if (WIFEXITED(status))
		g_exit_status = (WEXITSTATUS(status)); */
}

void	new_pipe(t_cmd *commands, t_pipe *data, char **envp)
{
	int		exit_code;
	char	*path;

	manage_redirections(commands, data);
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

	if (init_data(&data, commands) == 1)
		return (1);
	dup_original_stds(&data.dup_stdin, &data.dup_stdout);
	i = 0;
	while (commands)
	{
		if (pipe(data.fd) == -1)
			return (perror_return(&data, EXIT_FAILURE, "Pipe"));
		data.pid[i] = fork();
		if (data.pid[i] == -1)
			return (perror_return(&data, EXIT_FAILURE, "Fork"));
		else if (data.pid[i] == 0)
			new_pipe(commands, &data, envp);
		dup2(data.fd[0], STDIN_FILENO);
		close_pipe(data.fd[0], data.fd[1]);
		commands = commands->next;
		i++;
	}
	wait_childs(&data);
	return (0);
}
