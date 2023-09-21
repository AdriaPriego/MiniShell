/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:56:55 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/21 12:21:36 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*obtain_oldpwd(char **env)
{
	int	i;

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
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
			return (&env[i][4]);
		i++;
	}
	return (NULL);
}

int	ft_chdir(char *direct, char ***env)
{
	char	*oldpwd;
	char	*pwd;
	char	*tmp;

	oldpwd = obtain_pwd(*env);
	if (chdir(direct) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: cd: %s: ", direct);
		return (perror(NULL), 1);
	}
	pwd = getcwd(NULL, 0);
	if (oldpwd)
	{
		tmp = ft_strjoin("OLDPWD=", oldpwd);
		*env = ft_add_env(tmp, *env);
		free(tmp);
	}
	if (pwd)
	{
		tmp = ft_strjoin("PWD=", pwd);
		*env = ft_add_env(tmp, *env);
		free(tmp);
		free(pwd);
	}
	return (0);
}
