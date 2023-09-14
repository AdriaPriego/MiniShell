/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:45:12 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/14 13:53:48 by fbosch           ###   ########.fr       */
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

int	is_builtin(t_cmd *commands)
{
	if (commands && commands->args && commands->args[0])
	{
		if (ft_strcmp(commands->args[0], "echo") == 0)
			return (1);
		else if (ft_strcmp(commands->args[0], "cd") == 0)
			return (1);
		else if (ft_strcmp(commands->args[0], "pwd") == 0)
			return (1);
		else if (ft_strcmp(commands->args[0], "export") == 0)
			return (1);
		else if (ft_strcmp(commands->args[0], "unset") == 0)
			return (1);
		else if (ft_strcmp(commands->args[0], "env") == 0)
			return (1);
		else if (ft_strcmp(commands->args[0], "exit") == 0)
			return (1);
	}
	return (0);
}
int	execute_builtins(char **args, char ***envp, t_pipe *data, int exit_flag)
{
	int	exit_status;

	exit_status = 0;
	if (ft_strcmp(args[0], "echo") == 0)
		exit_status = ft_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		exit_status = ft_cd(args, *envp);
	else if (ft_strcmp(args[0], "pwd") == 0)
		exit_status = ft_pwd();
	else if (ft_strcmp(args[0], "export") == 0)
		exit_status = ft_export(args, envp);
	else if (ft_strcmp(args[0], "unset") == 0)
		exit_status = ft_unset(args, *envp);
	else if (ft_strcmp(args[0], "env") == 0)
		exit_status = ft_env(*envp);
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(args);
	if (exit_flag == FT_EXIT)
		exit(exit_status);
	dup2(data->dup_stdin, STDIN_FILENO);
	dup2(data->dup_stdout, STDOUT_FILENO);
	return (exit_status);
}

void	new_pipe(t_cmd *commands, t_pipe *data, char ***envp)
{
	int		exit_code;
	char	*path;

	manage_redirections(commands, data);
	if (is_builtin(commands))
		execute_builtins(commands->args, envp, data, FT_EXIT);
	exit_code = search_path(commands->args[0], *envp, &path);
	if (exit_code == CMD_NOT_FOUND)
		error_exit(data, exit_code, commands->args[0], MSSG_CMD_NOT_FOUND);
	else if (exit_code != 0)
		perror_exit(data, exit_code, commands->args[0]);
	execve(path, commands->args, *envp);
	perror_exit(data, EXIT_FAILURE, "Execve");
}

int	execute_commands(t_cmd *commands, char ***envp)
{
	t_pipe	data;
	int		i;

	if (init_data(&data, commands) == 1)
		return (1);
	dup_original_stds(&data.dup_stdin, &data.dup_stdout);
	if (data.n_cmds == 1 && is_builtin(commands))
	{
		//free(data.pid);
		manage_redirections(commands, &data);
		return (execute_builtins(commands->args, envp, &data, FT_NOEXIT));
	}
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
