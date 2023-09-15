/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:18:44 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/15 17:21:06 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_generate_new_env(char **command, char **env, int j, int i)
{
	while (env[j])
	{
		if (ft_strcmp_env(env[j], command[i]) == 0)
		{
			free(env[j]);
			while (env[j])
			{
				env[j] = env[j + 1];
				j++;
			}
		}
		if (env[j])
			j++;
	}
}
