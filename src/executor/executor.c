/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:45:12 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/15 13:31:26 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_childs(t_pipe *data, int *exit_s)
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
	if (WIFEXITED(status))
		*exit_s = (WEXITSTATUS(status));
	else
		*exit_s = 1;
}

void	new_pipe(t_cmd *commands, t_pipe *data, char ***envp, int *exit_s)
{
	int		exit_code;
	char	*path;

	manage_redirections(commands, data, FT_EXIT);
	if (is_builtin(commands))
		execute_builtins(commands->args, envp, exit_s, FT_EXIT);
	exit_code = search_path(commands->args[0], *envp, &path);
	if (exit_code == CMD_NOT_FOUND)
		error_exit(data, exit_code, commands->args[0], MSSG_CMD_NOT_FOUND);
	else if (exit_code != 0)
		perror_exit(data, exit_code, commands->args[0]);
	execve(path, commands->args, *envp);
	perror_exit(data, EXIT_FAILURE, "Execve");
}

int	exec_one_builtin(t_cmd *commands, t_pipe *data, char ***envp, int *exit_s)
{
	if (manage_redirections(commands, data, FT_RETURN) == 1)
	{
		*exit_s = 1;
		return (0);
	}
	free(data->pid);
	execute_builtins(commands->args, envp, exit_s, FT_RETURN);
	dup2(data->dup_stdin, STDIN_FILENO);
	dup2(data->dup_stdout, STDOUT_FILENO);
	return (0);
}

int	execute_commands(t_cmd *commands, char ***envp, int *exit_s)
{
	t_pipe	data;
	int		i;

	if (init_data(&data, commands) == 1)
		return (1);
	dup_original_stds(&data.dup_stdin, &data.dup_stdout);
	if (data.n_cmds == 1 && is_builtin(commands))
		return (exec_one_builtin(commands, &data, envp, exit_s));
	i = 0;
	while (commands)
	{
		if (pipe(data.fd) == -1)
			return (perror_return(&data, EXIT_FAILURE, "Pipe"));
		data.pid[i] = fork();
		if (data.pid[i] == -1)
			return (perror_return(&data, EXIT_FAILURE, "Fork"));
		else if (data.pid[i] == 0)
			new_pipe(commands, &data, envp, exit_s);
		dup2(data.fd[0], STDIN_FILENO);
		close_pipe(data.fd[0], data.fd[1]);
		commands = commands->next;
		i++;
	}
	wait_childs(&data, exit_s);
	return (0);
}
