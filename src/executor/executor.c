/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:45:12 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/07 17:00:57 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_pipe(t_cmd *commands, char **envp, int fd[2])
{
	char	*path = ft_strdup("/bin");

	perror("jaja");
	close(fd[0]);
	close(fd[1]);
	execve(path, commands->args, envp);
	return (1);
}

int	execute_commands(t_cmd *commands, char **envp)
{	
	int temp_in;
	int	temp_out;
	int		fd[2];
	pid_t	pid1;

	temp_in = dup(STDIN_FILENO);
	temp_out = dup(STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	if (pipe(fd) == -1)
		return (error_return("Minishell: Pipe: Error creating Pipe"));
	while (commands)
	{
		if (!commands->prev)
			dup2(fd[0], STDIN_FILENO);
		if (!commands->next)
			dup2(fd[1], temp_out);
		pid1 = fork();
		if (pid1 == 0)
			new_pipe(commands, envp, fd);
		commands = commands->next;
	}
	perror("jaja2");
	waitpid(pid1, NULL, 0);
	dup2(temp_in, STDIN_FILENO);
	dup2(temp_out, STDOUT_FILENO);
	perror("jaja3");
	return (0);
}
