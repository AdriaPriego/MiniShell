/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:45:12 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/08 20:22:10 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_childs(t_pipe *data)
{
	int	i;
	
	i = 0;
	while (i < data->n_cmds)
	{
		waitpid(data->pid[i], &data->exit_status, 0);
		i++;
	}
	if (WIFEXITED(data->exit_status))
		ft_printf("Exit: %i\n", (WEXITSTATUS(data->exit_status)));
}

int	check_files(char *file, int mode)
{
	if (mode == FILE_IN)
	{
		if (file != NULL && access(file, F_OK) == 0)
		{
			if (access(file, R_OK) != 0)
				return (1);
		}
		else
			return (1);
	}
	else if (mode == FILE_OUT)
	{
		if (file != NULL && access(file, F_OK) == 0)
			if (access(file, W_OK) != 0)
				return (1);
	}
	return (0);
	/* if (file != NULL && access(file, F_OK) == 0)
	{
		if (access(file, R_OK) != 0)
			perror(file);
	}
	else if (file != NULL)
		perror(file);
	if (access(output, F_OK) == 0)
	{
		if (access(output, W_OK) != 0)
			perror(output);
	} */
}
//No such file or directory -> 1
//Permission denied -> 1
int	manage_redirections(t_cmd *commands, t_pipe *data)
{
	t_io	*temp;
	int		status;

	temp = commands->redirect;
	if (!commands->prev && commands->next)
		dup2(data->fd[1], STDOUT_FILENO);
	else if (commands->prev && !commands->next)
		dup2(data->fd[0], STDIN_FILENO);
	else if (commands->prev && commands->next)
	{
		dup2(data->fd[0], STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
	}
	while (temp)
	{
		if (temp->type == IN || temp->type == HERE_DOC)
			status = check_files(temp->file, FILE_IN);
		else if (temp->type == OUT_TRUNC || temp->type == OUT_APPEND)
			status = check_files(temp->file, FILE_OUT);
		if (status != 0)
			perror_exit(status, temp->file);
		if (temp->type == IN)
		{
			data->fd_input = open(temp->file, O_RDONLY);
			if (data->fd_input < 0)
				perror_exit(1, temp->file);
			dup2(data->fd_input, STDIN_FILENO);
		}
		else if (temp->type == OUT_TRUNC)
		{
			data->fd_output = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (data->fd_output < 0)
				perror_exit(1, temp->file);
			dup2(data->fd_output, STDOUT_FILENO);
		}
		else if (temp->type == OUT_APPEND)
		{
			data->fd_output = open(temp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (data->fd_output < 0)
				perror_exit(1, temp->file);
			dup2(data->fd_output, STDOUT_FILENO);
		}
		temp = temp->next;
	}
}
void	new_pipe(t_cmd *commands, t_pipe *data, char **envp)
{
	int		exit_code;
	char	*path;

	manage_redirections(commands, data);
	close(data->fd[0]);
	close(data->fd[1]);
	exit_code = search_path(commands->args[0], envp, &path);
	if (exit_code != EXIT_SUCCESS)                  //MANAGE COMMAND NOT FOUND && COMMAND NO ACCESS (PERROR DOESN'T DO IT)
		perror_exit(exit_code, commands->args[0]);
	execve(path, commands->args, envp);
	perror_exit(EXIT_FAILURE, "Execve:");
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

int	execute_commands(t_cmd *commands, char **envp)
{
	t_pipe	data;
	int	i;

	if (!commands)
		return (0);
	if (init_data(&data, commands) == 1)
		return (1);
	if (pipe(data.fd) == -1)
		perror_exit(EXIT_FAILURE, "Pipe:");
	i = 0;
	while (commands)
	{
		data.pid[i] = fork();
		if (data.pid[i] == -1)
			perror_exit(EXIT_FAILURE, "Fork:");
		else if (data.pid[i] == 0)
			new_pipe(commands, &data, envp);
		commands = commands->next;
		i++;
	}
	close(data.fd[0]);
	close(data.fd[1]);
	wait_childs(&data);
	return (0);
}
