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

int	calc_len_expan_file(char *str, char **env, int status)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			i += calc_len_value_expan(&str[i], env, status, &len);
		else
			len++;
		i++;
	}
	return (len);
}

void	check_expand_file(char *word, int exit, char *str, char **env)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '$')
		{
			if (ft_strncmp(&word[i], "$?", 2) == 0)
				value = ft_itoa(exit);
			else
				value = expand(&word[i], env);
			expand_var(&word[i], value, str,
				calc_len_expan_file(word, env, exit));
			i += ft_omit_var(&word[i]) - 1;
			j = ft_strlen(str);
		}
		else
			str[j++] = word[i];
		i++;
	}
	str[j] = '\0';
}

int	expand_file(char *path, char **env, int exit)
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
	status = expand_vars_file(file, aux, env, exit);
	if (status == 1)
		return (ft_matrix_free(file), ft_matrix_free(aux), 1);
	status = rewrite_file(path, aux);
	if (status == 1)
		return (ft_matrix_free(file), ft_matrix_free(aux), 1);
	ft_matrix_free(file);
	ft_matrix_free(aux);
	return (0);
}

int	expansor_files(t_cmd *comands, char **env, int status)
{
	t_io	*aux;

	while (commands)
	{
		aux = commands->redirect;
		while (aux)
		{
			if (aux->type == HERE_DOC)
			{
				if (expand_file(aux->file, env, status) == 1)
					return (1);
			}
			aux = aux->next;
		}
		commands = commands->next;
	}
	return (0);
}
