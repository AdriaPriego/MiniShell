/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:02:30 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/12 16:53:57 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_cd(char **comands)
{
	if (!comands[1])
		chdir(find_home());
	else if (ft_strcmp(comands[1], "..") == 0)
		chdir("..");
	else if (ft_strcmp(comands[1], ".") == 0)
		chdir(".");
	else if (ft_strcmp(comands[1], "/") == 0)
		chdir("/");
	else if (ft_strcmp(comands[1], "~") == 0)
		chdir(find_home());
	else if (chdir(comands[1]) != 0)
		ft_printf_fd(2, "minishell: cd: %s: No such file or directory\n",
			comands[1]);
}

void	ft_pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	ft_printf("%s\n", str);
	free(str);
}

void	ft_env(void)
{
	int	i;

	i = 0;
	while (g_global.env[i])
	{
		ft_printf("%s\n", g_global.env[i]);
		i++;
	}
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
}

int	ft_unset(char **comand)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (g_global.env[i])
	{
		str = ft_strdup(g_global.env[i]);
		if (!str)
			return (1);
		if (ft_strcmp(str, comand[1]) == 0)
		{
			j = i;
			free(g_global.env[j]);
			while (g_global.env[j])
			{
				g_global.env[j] = g_global.env[j + 1];
				j++;
			}
		}
		else
			i++;
		free(str);
	}
	return (0);
}
