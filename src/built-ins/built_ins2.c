/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:47:17 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/14 10:45:20 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_add_env(char *str, char **env)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * (ft_array_len(env) + 2));
	if (!tmp)
		return (NULL);
	while (env[i])
	{
		tmp[i] = ft_strdup(env[i]);
		i++;
	}
	tmp[i] = ft_strdup(str);
	tmp[i + 1] = NULL;
	ft_matrix_free(env);
	return (tmp);
}

int	check_format_export(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	if (str[i] != '=')
	{
		return (1);
	}
	return (0);
}

void	ft_export(char **args, char **env)
{
	int	i;

	i = 1;
	if (!args[1])
		ft_env(env);
	else
	{
		while (args[i])
		{
			if (check_format_export(args[i]) == 0)
			{
				ft_add_env(args[i], env);
			}
			else
			{
				ft_printf_fd(STDERR_FILENO,
					"minishell: export: `%s': not a valid identifier\n", args[i]);
				exit(1);
			}
			i++;
		}
	}
	exit(0);
}

void	ft_exit(char **args)
{
	int	i;

	i = 0;
	if (ft_array_len(args) > 2)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: exit: too many arguments\n");
		exit(1);
	}
	if (args[1])
	{
		if (ft_test_int(args[1]) != 0)
		{
			ft_printf("exit\n");
			ft_printf_fd(STDERR_FILENO,
				"minishell: exit: %s: numeric argument required\n", args[1]);
			exit(255);
		}
		else
		{
			ft_printf("exit\n");
			exit(ft_atoi(args[1]));
		}
	}
	ft_printf("exit\n");
	exit(0);
}
