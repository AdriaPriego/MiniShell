/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:20:35 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/15 17:21:46 by fbosch           ###   ########.fr       */
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
