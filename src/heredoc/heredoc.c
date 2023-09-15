/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:09:24 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/15 17:41:47 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_heredoc(char *delimiter, char *path)
{
	char	*str;
	int		fd;

	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	str = readline("> ");
	while (str && ft_strcmp(delimiter, str) != 0)
	{
		str = ft_strjoin_line(str, "\n");
		ft_putstr_fd(str, fd);
		free(str);
		str = readline("> ");
	}
	close(fd);
	free(str);
	init_signals(DEFAULT);
}

void	do_heredoc(int i, t_io *aux)
{
	char	*num;
	char	*path;

	num = ft_itoa(i);
	path = ft_strjoin("/tmp/minishell", num);
	free(num);
	create_heredoc(aux->file, path);
	free(aux->file);
	aux->file = ft_strdup(path);
	free(path);
}

int	heredoc(t_cmd *commands)
{
	t_io	*aux;
	int		i;

	i = 0;
	while (commands)
	{
		aux = commands->redirect;
		while (aux)
		{
			if (aux->type == HERE_DOC)
			{
				do_heredoc(i, aux);
				i++;
			}
			aux = aux->next;
		}
		commands = commands->next;
	}
	return (0);
}
