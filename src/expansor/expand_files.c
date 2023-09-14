/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:35:53 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/14 12:31:42 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	expand_file(char *path, char **env)
{
	char	**file;
	char	**aux;
	int		status;

	file = malloc((calc_len_file(path) + 1) * sizeof (char *));
	if (!file)
		return (1);
	aux = malloc((calc_len_file(path) + 1) * sizeof (char *));
	if (!aux)
		return (free(file), 1);
	if (fill_aux(path, file) == 1)
		return (ft_matrix_free(file), ft_matrix_free(aux), 1);
	status = expand_vars_file(file, aux, env);
	if (status == 1)
		return (ft_matrix_free(file), ft_matrix_free(aux), 1);
	status = rewrite_file(path, aux);
	if (status == 1)
		return (ft_matrix_free(file), ft_matrix_free(aux), 1);
	ft_matrix_free(file);
	ft_matrix_free(aux);
	return (0);
}

int	expansor_files(t_cmd *commands, char **env)
{
	t_io	*aux;

	while (commands)
	{
		aux = commands->redirect;
		while (aux)
		{
			if (aux->type == HERE_DOC)
			{
				if (expand_file(aux->file, env) == 1)
					return (1);
			}
			aux = aux->next;
		}
		commands = commands->next;
	}
	return (0);
}
