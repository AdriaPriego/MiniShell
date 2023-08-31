/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:47:17 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/31 13:13:05 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_export(char **comand, char **envp)
{
	int		i;
	char	**aux;

	i = 0;
	aux = ft_splitn(comand[2], ' ', 2);
	while (envp[i])
		i++;
	envp[i] = ft_strdup(aux[1]);
	envp[i + 1] = NULL;
	ft_free_matrix((const char **)aux, ft_array_len(aux) - 1);
}
