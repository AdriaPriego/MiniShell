/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:02:30 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/15 13:02:41 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_cd(char **comands, char **env)
{
	if (!comands[1])
		chdir(find_home(env));
	else if (ft_strcmp(comands[1], "..") == 0)
		chdir("..");
	else if (ft_strcmp(comands[1], ".") == 0)
		chdir(".");
	else if (ft_strcmp(comands[1], "/") == 0)
		chdir("/");
	else if (ft_strcmp(comands[1], "~") == 0)
		chdir(find_home(env));
	else if (chdir(comands[1]) != 0)
	{
		ft_printf_fd(2, "minishell: cd: %s: No such file or directory\n",
			comands[1]);
		exit(1);
	}
	exit(0);
}

void	ft_pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	ft_printf("%s\n", str);
	free(str);
	exit(0);
}

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
	exit (0);
}

void	ft_echo(char **comand)
{
	int	i;

	if (ft_strcmp(comand[1], "-n") == 0)
	{
		i = 2;
		ft_print_matrix(comand, i);
	}
	else
	{
		i = 1;
		ft_print_matrix(comand, i);
		ft_printf("\n");
	}
	exit (0);
}

void	ft_unset(char **comand, char **env)
{
	int	i;
	int	j;

	i = 1;
	while (comand[i])
	{
		if (valid_comand(comand[i]))
		{
			ft_printf_fd(2, "minishell: unset: `%s': not a valid identifier\n",
				comand[i]);
			exit(1);
		}
		j = 0;
		while (env[j])
		{
			if (ft_strcmp_env(env[j], comand[i]) == 0)
			{
				free(env[j]);
				env[j] = NULL;
			}
			j++;
		}
		i++;
	}
	exit (0);
}
