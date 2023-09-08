/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:45:12 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/08 02:21:42 by fbosch           ###   ########.fr       */
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

void	new_pipe(t_cmd *commands, t_pipe *data, char **envp)
{
	int		exit_code;
	char	*path;
	
	exit_code = search_path(commands->args[0], envp, &path);
	if (exit_code != EXIT_SUCCESS)                  //MANAGE COMMAND NOT FOUND && COMMAND NO ACCESS (PERROR DOESN'T DO IT)
		perror_exit(exit_code, commands->args[0]);
	close(data->fd[0]);
	close(data->fd[1]);
	execve(path, commands->args, envp);
	perror_exit(EXIT_FAILURE, "Execve:");
}

int	execute_commands(t_cmd *commands, char **envp)
{
	t_pipe	data;
	int	i;
	int	temp_in;
	int	temp_out;

	temp_in = dup(STDIN_FILENO);
	temp_out = dup(STDOUT_FILENO);
	pipe(data.fd);
	dup2(data.fd[1], STDOUT_FILENO);
	dup2(data.fd[0], STDIN_FILENO);
	if (!commands)
		return (0);
	data.n_cmds = count_commands(commands);
	data.pid  = malloc(sizeof(pid_t) * data.n_cmds);
	if (!data.pid)
		return (1);
	i = 0;
	while (commands)
	{
		if (i == 0)
			dup2(temp_in, STDIN_FILENO);
		if (i == data.n_cmds - 1)
			dup2(temp_out, STDOUT_FILENO);
		data.pid[i] = fork();
		if (data.pid[i] == -1)
			perror_exit(EXIT_FAILURE, "Pipe:");
		else if (data.pid[i] == 0)
			new_pipe(commands, &data, envp);
		commands = commands->next;
		i++;
	}
	close(data.fd[0]);
	close(data.fd[1]);
	wait_childs(&data);
	dup2(temp_in, STDIN_FILENO);
	dup2(temp_out, STDOUT_FILENO);
	return (0);
}
