/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:35:16 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/18 13:17:34 by apriego-         ###   ########.fr       */
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

t_env	*ft_dup_matrix_env(char **envp)
{
	t_env	*dup;
	int		i;

	i = 0;
	dup = malloc(sizeof(t_env));
	if (!dup)
		return (NULL);
	dup->env = malloc((ft_array_len(envp) + 1) * sizeof(char *));
	if (!dup->env)
		return (free(dup), NULL);
	dup->export = malloc((ft_array_len(envp) + 1) * sizeof(char *));
	if (!dup->export)
		return (free(dup->env), free(dup), NULL);
	while (envp[i])
	{
		dup->env[i] = ft_strdup(envp[i]);
		if (!dup->env[i])
			return (ft_free_matrix(dup->env, i), free(dup), NULL);
		dup->export[i] = ft_strdup_export(envp[i]);
		if (!dup->export[i])
			return (ft_free_matrix(dup->env, i), ft_free_matrix(dup->export, i), free(dup), NULL);
		i++;
	}
	dup->env[i] = NULL;
	dup->export[i] = NULL;
	return (dup);
}
