/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:35:16 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/14 13:46:57 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strlen_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_print_matrix(char **matrix, int i)
{
	while (matrix[i])
	{
		ft_printf("%s", matrix[i++]);
		if (matrix[i])
			ft_printf(" ");
	}
}

char	*ft_strdup_chr(char *str, char c)
{
	int		i;
	char	*dup;

	i = 0;
	dup = malloc(ft_strlen_chr(str, c) + 1);
	if (!dup)
		return (NULL);
	while (str[i] != c && str[i] != '\0')
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}

char	**ft_dup_matrix(char **envp)
{
	char	**dup;
	int		i;

	i = 0;
	dup = malloc((ft_array_len(envp) + 1) * sizeof(char *));
	if (!dup)
		return (NULL);
	while (envp[i])
	{
		dup[i] = ft_strdup(envp[i]);
		if (!dup[i])
			return (ft_free_matrix((const char **)dup, i));
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

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
