/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 01:12:21 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/13 18:26:08 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	check_access(char *file, int mode)
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
}

void	check_files(t_pipe *data, t_io *temp)
{
	int	status;

	if (temp->type == IN || temp->type == HERE_DOC)
		status = check_access(temp->file, FILE_IN);
	else if (temp->type == OUT_TRUNC || temp->type == OUT_APPEND)
		status = check_access(temp->file, FILE_OUT);
	if (status != 0)
		perror_exit(data, status, temp->file);
} */
void	close_pipe(int in, int out)
{
	close(in);
	close(out);
}

void	dup_custom_redirections(t_pipe *data, t_io *temp)
{
	if (temp->type == IN || temp->type == HERE_DOC)
	{
		data->fd_in = open(temp->file, O_RDONLY);
		if (data->fd_in < 0)
			perror_exit(data, EXIT_FAILURE, temp->file);
		dup2(data->fd_in, STDIN_FILENO);
		close(data->fd_in);
		/* if (temp->type == HERE_DOC)   WILL HAVE TO CHECK
			unlink(temp->type); */
	}
	else if (temp->type == OUT_TRUNC || temp->type == OUT_APPEND)
	{
		if (temp->type == OUT_TRUNC)
			data->fd_out = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			data->fd_out = open(temp->file, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		if (data->fd_out < 0)
			perror_exit(data, EXIT_FAILURE, temp->file);
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
	}
}

void	manage_redirections(t_cmd *commands, t_pipe *data)
{
	t_io	*temp;

	if (commands->next != NULL)
		dup2(data->fd[1], STDOUT_FILENO);
	close_pipe(data->fd[0], data->fd[1]);
	temp = commands->redirect;
	while (temp)
	{
		dup_custom_redirections(data, temp);
		temp = temp->next;
	}
}
