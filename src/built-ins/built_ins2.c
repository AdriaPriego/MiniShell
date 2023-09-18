/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:47:17 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/18 18:45:38 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_add_env(char *str, char **env)
{
	char	**tmp;
	int		i;
	int		sust_flag;

	sust_flag = 0;
	i = 0;
	tmp = malloc(sizeof(char *) * (ft_array_len(env) + 2));
	if (!tmp)
		return (NULL);
	while (env[i])
	{
		if (ft_strcmp_env(env[i], str) == 0)
		{
			tmp[i] = ft_strdup(str);
			sust_flag = 1;
		}
		else
			tmp[i] = ft_strdup(env[i]);
		i++;
	}
	if (sust_flag == 0)
		tmp[i++] = ft_strdup(str);
	tmp[i] = NULL;
	ft_matrix_free(env);
	return (tmp);
}

char	**ft_add_export(char *str, char **export)
{
	char	**tmp;
	int		i;
	int		sust_flag;

	sust_flag = 0;
	i = 0;
	tmp = malloc(sizeof(char *) * (ft_array_len(export) + 2));
	if (!tmp)
		return (NULL);
	while (export[i])
	{
		if (ft_strcmp_env(export[i], str) == 0)
		{
			tmp[i] = ft_strdup_export(str);
			sust_flag = 1;
		}
		else
			tmp[i] = ft_strdup(export[i]);
		i++;
	}
	if (sust_flag == 0)
		tmp[i++] = ft_strdup_export(str);
	tmp[i] = NULL;
	ft_matrix_free(export);
	return (tmp);
}

t_env	*ft_add_env_export(char *str, t_env *env)
{
	env->env = ft_add_env(str, env->env);
	env->export = ft_add_export(str, env->export);
	return (env);
}


int	ft_export(char **args, t_env *env)
{
	int	i;
	int	exit_s;

	i = 1;
	exit_s = 0;
	if (!args[1])
		ft_print_export(env->export);
	else
	{
		while (args[i])
		{
			if (check_format_export(args[i]) == 0)
				env = ft_add_env_export(args[i], env);
			else if (check_format_export(args[i]) == 2)
				ft_add_export(args[i], env->export);
			else
			{
				ft_printf_fd(STDERR_FILENO, MSSG_EXPORT_ERR, args[i]);
				exit_s = 1;
			}
			i++;
		}
	}
	return (exit_s);
}

void	ft_exit(char **args, int *exit_s)
{
	if (ft_array_len(args) > 2)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: exit: too many arguments\n");
		exit (1);
	}
	if (args[1])
	{
		if (ft_test_int(args[1]) != 0)
		{
			//ft_printf("exit\n");
			ft_printf_fd(STDERR_FILENO,
				"minishell: exit: %s: numeric argument required\n", args[1]);
			exit (255);
		}
		else
		{
			//ft_printf("exit\n");
			exit (ft_atoi(args[1]));
		}
	}
	//ft_printf("exit\n");
	exit (*exit_s);
}
