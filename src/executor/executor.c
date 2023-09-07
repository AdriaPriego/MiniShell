/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:45:12 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/07 21:56:19 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_pipe(t_cmd *commands, char **envp)
{
	int		exit_code;
	char	*path;
	
	exit_code = search_path(commands->args[0], envp, &path);
	if (exit_code != EXIT_SUCCESS)                  //MANAGE COMMAND NOT FOUND && COMMAND NO ACCESS (PERROR DOESN'T DO IT)
		perror_exit(exit_code, commands->args[0]);
	execve(path, commands->args, envp);
	perror_exit(EXIT_FAILURE, MSSG_EXECVE_ERR);
}

int	execute_commands(t_cmd *commands, char **envp)
{
	t_pipe	data;

	if (!commands)
		return (0);
	while (commands)
	{
		data.pid = fork();
		if (data.pid == 0)
			new_pipe(commands, envp);
		commands = commands->next;
	}
	waitpid(data.pid, &data.exit_status, 0);
	if (WIFEXITED(data.exit_status))
		printf("Exit: %i\n", (WEXITSTATUS(data.exit_status)));
	return (0);
}
