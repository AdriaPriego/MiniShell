/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:47:17 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/15 03:16:07 by fbosch           ###   ########.fr       */
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
		if (strncmp(env[i], str, ft_strlen_chr(env[i], '=')) == 0)
		{
			tmp[i] = ft_strdup(str);
			sust_flag = 1;
		}
		else
			tmp[i] = ft_strdup(env[i]);
		i++;
	}
	if (sust_flag == 0)
		tmp[i] = ft_strdup(str);
	tmp[i + 1] = NULL;
	ft_matrix_free(env);
	return (tmp);
}

int	check_format_export(char *str)
{
	int	i;

	i = 0;
	while (ft_isalpha(str[i]) == 1 && str[i] != '\0')
		i++;
	if (str[i] != '=')
		return (1);
	return (0);
}

int	ft_export(char **args, char ***env)
{
	int	i;

	i = 1;
	if (!args[1])
		ft_print_export(*env);
	else
	{
		while (args[i])
		{
			if (check_format_export(args[i]) == 0)
				*env = ft_add_env(args[i], *env);
			else
			{
				ft_printf_fd(STDERR_FILENO,
					"minishell: export: `%s': not a valid identifier\n", args[i]);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

void	ft_exit (char **args)
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
	exit (g_exit_status);
}
