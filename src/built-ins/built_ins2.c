/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:47:17 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/08 17:08:12 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_add_env(char *str)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * (ft_array_len(g_global.env) + 2));
	if (!tmp)
		return (NULL);
	while (g_global.env[i])
	{
		tmp[i] = ft_strdup(g_global.env[i]);
		i++;
	}
	tmp[i] = ft_strdup(str);
	tmp[i + 1] = NULL;
	ft_matrix_free(g_global.env);
	return (tmp);
}

int	check_format_export(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (ft_printf("ERROR\n"));
		i++;
	}
	if (str[i] != '=')
	{
		return (ft_printf("ERROR\n"));
	}
	return (0);
}

void	ft_export(char **args)
{
	int	i;

	i = 1;
	if (!args[1])
		ft_env();
	else
	{
		while (args[i])
		{
			if (check_format_export(args[i]) == 0)
			{
				ft_add_env(args[i]);
			}
			i++;
		}
	}
}
