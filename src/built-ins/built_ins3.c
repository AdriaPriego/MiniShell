/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:18:44 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/21 13:20:37 by apriego-         ###   ########.fr       */
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

int	ft_test_options_echo(char **command, int *i)
{
	int	j;
	int	check;

	check = 0;
	while (command[*i] && command[*i][0] == '-')
	{
		j = 1;
		while (command[*i][j])
		{
			if (command[*i][j] != 'n')
				return (check);
			j++;
		}
		*i += 1;
		check = 1;
	}
	return (check);
}

int	ft_strcmp_export(char *export, char *str)
{
	int	i;

	i = 0;
	while (export[i] != '=' && str[i] != '\0')
	{
		if (export[i] != str[i])
			return (export[i] - str[i]);
		i++;
	}
	if (export[i] == '=' && str[i] == '\0')
		return (0);
	return (export[i] - str[i]);
}

int	check_format_export(char *str)
{
	int	i;

	i = 0;
	while ((ft_isalpha(str[i]) == 1 || str[i] == '_') && str[i] != '\0')
		i++;
	if (ft_strncmp(&str[i], "+=", 2) == 0 && i != 0)
		return (3);
	if (str[i] == '\0')
		return (2);
	if (str[i] != '=' || i == 0)
		return (1);
	return (0);
}

t_env	*ft_join_env_export(char *str, t_env *env)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '+' || flag == 1)
		{
			flag = 1;
			str[i] = str[i + 1];
		}
		i++;
	}
	str[i] = '\0';
	env->env = ft_join_env(str, env->env);
	env->export = ft_join_export(str, env->export);
	return (env);
}
