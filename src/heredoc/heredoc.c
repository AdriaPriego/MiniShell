/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:09:24 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/08 20:00:42 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	do_heredoc(char *delimiter, char *path)
{
	char	*str;
	int		fd;

	fd = open(path, O_CREAT | O_WRONLY, 0666);
	str = readline("> ");
	while (ft_strcmp(delimiter, str) != 0)
	{
		str = ft_strjoin_line(str, "\n");
		ft_putstr_fd(str, fd);
		free(str);
		str = readline("> ");
	}
	close(fd);
	free(str);
}

int	heredoc(t_cmd *commands)
{
	char	*path;
	char	*num;
	int		i;

	i = 0;
	while (commands)
	{
		while (commands->redirect)
		{
			if (commands->redirect->type == HERE_DOC)
			{
				num = ft_itoa(i);
				path = ft_strjoin("/tmp/minishell", num);
				free(num);
				do_heredoc(commands->redirect->file, path);
				free(commands->redirect->file);
				commands->redirect->file = ft_strdup(path);
				free(path);
				i++;
			}
			commands->redirect = commands->redirect->next;
		}
		commands = commands->next;
	}
	return (0);
}
