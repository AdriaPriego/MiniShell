/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:47:17 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/20 20:19:02 by apriego-         ###   ########.fr       */
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

char	*ft_strdup_join(char *str)
{
	int		i;
	char	*dup;

	i = 0;
	dup = malloc(ft_strlen(str));
	if (!dup)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != '+')
			dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin_export(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		flag;

	i = 0;
	j = 0;
	flag = 0;
	str = malloc(ft_strlen(s1) + ft_strlen(s2));
	if (!str)
		return (NULL);
	while (s1[i] != C_TWO_QUOTE || flag == 0)
	{
		if (s1[i] == C_TWO_QUOTE)
			flag = 1;
		else
			str[i] = s1[i];
		i++;
	}	
	while (s2[j] != '=')
		j++;
	j++;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = C_TWO_QUOTE;
	str[i + 1] = '\0';
	return (str);
}

char	*ft_strjoin_env(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(ft_strlen(s1) + ft_strlen(s2));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '=')
		j++;
	j++;
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_join_env(char *str, char **env)
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
			tmp[i] = ft_strjoin_env(env[i], str);
			sust_flag = 1;
		}
		else
			tmp[i] = ft_strdup(env[i]);
		i++;
	}
	if (sust_flag == 0)
		tmp[i++] = ft_strdup_join(str);
	tmp[i] = NULL;
	ft_matrix_free(env);
	return (tmp);
}

char	**ft_join_export(char *str, char **export)
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
		if (ft_strcmp_export(export[i], str) == 0)
		{
			tmp[i] = ft_strjoin_export(export[i], str);
			sust_flag = 1;
		}
		else
			tmp[i] = ft_strdup(export[i]);
		i++;
	}
	if (sust_flag == 0)
		tmp[i++] = ft_strdup_join(str);
	tmp[i] = NULL;
	ft_matrix_free(export);
	return (tmp);
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

int	ft_export(char **args, t_env *env)
{
	int	i;
	int	exit_s;

	(1 && (i = 1) && (exit_s = 0));
	if (!args[1])
		ft_print_export(env->export);
	else
	{
		while (args[i])
		{
			if (check_format_export(args[i]) == 0)
				env = ft_add_env_export(args[i], env);
			else if (check_format_export(args[i]) == 3)
				env = ft_join_env_export(args[i], env);
			else if (check_format_export(args[i]) == 2)
				env->export = ft_add_export(args[i], env->export);
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
	if (args[1] && ft_strcmp(args[1], "--") == 0)
	{
		// ft_printf("exit\n");
		exit(*exit_s);
	}
	else if (args[1] && ft_test_int(args[1]) != 0)
	{
		// ft_printf("exit\n");
		ft_printf_fd(STDERR_FILENO, MSSG_EXIT_NUM_ERR, args[1]);
		exit(255);
	}
	else if (args[1])
	{
		if (ft_array_len(args) > 2)
		{
			ft_printf_fd(STDERR_FILENO,
				"minishell: exit: too many arguments\n");
			*exit_s = 1;
			return ;
		}
		// ft_printf("exit\n");
		exit(ft_atoi(args[1]));
	}
	// ft_printf("exit\n");
	exit(*exit_s);
}
