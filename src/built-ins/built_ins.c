/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:02:30 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/20 15:31:55 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*obtain_oldpwd(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
			return (&env[i][7]);
		i++;
	}
	return (NULL);
}

char	*obtain_pwd(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
			return (&env[i][4]);
		i++;
	}
	return (NULL);
}

int ft_chdir(char *direct, char ***env)
{
	char	*oldpwd;
	char	*pwd;
	char	*tmp;

	oldpwd = obtain_pwd(*env);
	//ft_printf("AAAAAAAAAAAAAA");
	if (chdir(direct) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: cd: %s: ", direct);
		perror(NULL);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	tmp = ft_strjoin("OLDPWD=", oldpwd);
	*env = ft_add_env(tmp, *env);
	free(tmp);
	tmp = ft_strjoin("PWD=", pwd);
	*env = ft_add_env(tmp, *env);
	free(tmp);
	free(pwd);
	return (0);
}

int	ft_cd(char **commands, char ***env)
{
	int		i;
	char	*str;

	if (!commands[1])
		return (ft_chdir(find_home(*env), env));
	else if (!*commands[1])
		return (0);
	else if (ft_strcmp(commands[1], "..") == 0)
		return (ft_chdir("..", env));
	else if (ft_strcmp(commands[1], ".") == 0)
		return (ft_chdir(".", env));
	else if (ft_strcmp(commands[1], "/") == 0)
		return (ft_chdir("/", env));
	else if (ft_strcmp(commands[1], "~") == 0)
		return (ft_chdir(find_home(*env), env));
	else if (ft_strcmp(commands[1], "-") == 0)
	{
		str = ft_strdup(obtain_oldpwd(*env));
		i = ft_chdir(obtain_oldpwd(*env), env);
		if (i == 0)
			ft_printf("%s\n", str);
		free(str);
		return (i);
	}
	return (ft_chdir(commands[1], env));
}

int	ft_pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	ft_printf("%s\n", str);
	free(str);
	return (0);
}

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

int	ft_echo(char **command)
{
	int	i;

	i = 1;
	if (!command[1])
		ft_printf("\n");
	else if (ft_test_options_echo(command, &i))
	{
		ft_print_matrix(command, i);
	}
	else
	{
		ft_print_matrix(command, i);
		ft_printf("\n");
	}
	return (0);
}

int	ft_unset(char **command, t_env *env)
{
	int	i;
	int	j;

	i = 1;
	while (command[i])
	{
		if (valid_command(command[i]))
		{
			ft_printf_fd(2, "minishell: unset: `%s': not a valid identifier\n",
				command[i]);
			return (1);
		}
		j = 0;
		ft_generate_new_env(command, env->env, j, i);
		i++;
	}
	return (0);
}
