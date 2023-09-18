/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:20:35 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/18 17:42:54 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_matrix_free(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	ft_strcmp_env(char *env, char *str)
{
	int	i;

	i = 0;
	while (env[i] != '=' && str[i] != '\0')
	{
		if (env[i] != str[i])
			return (env[i] - str[i]);
		i++;
	}
	if (env[i] == '=' && str[i] == '\0')
		return (0);
	return (env[i] - str[i]);
}

char	**ft_free_matrix(char **matrix, int j)
{
	while (j > 0)
	{
		j--;
		free((void *)matrix[j]);
	}
	free(matrix);
	return (NULL);
}

char *ft_strdup_export(char *envp)
{
	int		i;
	char	*dup;

	i = 0;
	dup = malloc(ft_strlen(envp) + 3);
	if (!dup)
		return (NULL);
	while (envp[i] != '=' && envp[i] != '\0')
	{
		dup[i] = envp[i];
		i++;
	}
	if (envp[i] == '=')
	{
		dup[i] = envp[i];
		dup[++i] = C_TWO_QUOTE;
		while (envp[i] != '\0')
		{
			dup[i + 1] = envp[i];
			i++;
		}
		dup[i + 1] = C_TWO_QUOTE;
		dup[i + 2] = '\0';
	}
	return (dup);
}

