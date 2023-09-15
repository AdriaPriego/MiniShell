/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:02:30 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/15 14:20:39 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_cd(char **commands, char **env)
{
	if (!commands[1])
		chdir(find_home(env));
	else if (!*commands[1])
		return (0);
	else if (ft_strcmp(commands[1], "..") == 0)
		chdir("..");
	else if (ft_strcmp(commands[1], ".") == 0)
		chdir(".");
	else if (ft_strcmp(commands[1], "/") == 0)
		chdir("/");
	else if (ft_strcmp(commands[1], "~") == 0)
		chdir(find_home(env));
	else if (chdir(commands[1]) != 0)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: cd: %s: ", commands[1]);
		perror(NULL);
		return (1);
	}
	return (0);
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

	if (!command[1])
		ft_printf("\n");
	else if (ft_strcmp(command[1], "-n") == 0)
	{
		i = 2;
		ft_print_matrix(command, i);
	}
	else
	{
		i = 1;
		ft_print_matrix(command, i);
		ft_printf("\n");
	}
	return (0);
}

int	ft_unset(char **command, char **env)
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
		i++;
	}
	return (0);
}
