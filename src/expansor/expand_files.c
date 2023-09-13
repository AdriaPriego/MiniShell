/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:35:53 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/13 18:27:32 by apriego-         ###   ########.fr       */
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

int	expansor_files(t_cmd *comands, char **env)
{
	t_io	*aux;

	while (comands)
	{
		aux = comands->redirect;
		while (aux)
		{
			if (aux->type == HERE_DOC)
			{
				if (expand_file(aux->file, env) == 1)
					return (1);
			}
			aux = aux->next;
		}
		comands = comands->next;
	}
	return (0);
}
