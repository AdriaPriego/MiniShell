/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:35:53 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/12 18:39:28 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	rewrite_file(char *path, char **aux)
{
	int	fd;
	int	i;

	fd = open(path, O_TRUNC | O_WRONLY);
	i = 0;
	ft_printf("HOLA");
	while (aux[i])
	{
		ft_printf_fd(fd, "%s", aux[i]);
		i++;
	}
	close(fd);
	return (0);
}

int	calc_len_file(char *path)
{
	int		fd;
	char	*str;
	int		len;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	str = get_next_line(fd);
	if (!str)
		return (0);
	len = 1;
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		len++;
	}
	close(fd);
	return (len);
}

int	fill_aux(char *path, char **file)
{
	int		fd;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	i = 0;
	file[i] = get_next_line(fd);
	while (file[i])
	{
		i++;
		file[i] = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	expand_file(char *path)
{
	char	**file;
	char	**aux;
	int		i;
	t_quote quote;

	file = malloc((calc_len_file(path) + 1) * sizeof (char *));
	if (!file)
		return (1);
	aux = malloc((calc_len_file(path) + 1) * sizeof (char *));
	if (!aux)
		return (free(file), 1);
	if (fill_aux(path, file) == 1)
	{
		ft_matrix_free(file);
		return (1);
	}
	init_quote(&quote);
	i = 0;
	while (file[i])
	{
		aux[i] = malloc(calc_len_expanded(file[i]) + 1);
		aux[i][0] = '\0';
		check_expand(file[i], &quote, aux[i]);
		i++;
	}
	aux[i] = NULL;
	rewrite_file(path, aux);
	return (0);
}

int	expansor_files(t_cmd *comands)
{
	t_io	*aux;

	while (comands)
	{
		aux = comands->redirect;
		while (aux)
		{
			if (aux->type == HERE_DOC)
			{
				if (expand_file(aux->file) == 1)
					return (1);
			}
			aux = aux->next;
		}
		comands = comands->next;
	}
	return (0);
}
