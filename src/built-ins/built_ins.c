/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:02:30 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/31 15:50:56 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_cd(char **comand, char **envp)
{
	char	**str;

	str = ft_split(comand[2], ' ');
	if (ft_strncmp(str[0], "cd", ft_strlen(str[0])) == 0)
	{
		if (!str[1])
			chdir(find_home(envp));
		else if (ft_strncmp(str[1], "..", ft_strlen(str[1])) == 0)
			chdir("..");
		else if (ft_strncmp(str[1], ".", ft_strlen(str[1])) == 0)
			chdir(".");
		else if (ft_strncmp(str[1], "/", ft_strlen(str[1])) == 0)
			chdir("/");
		else if (ft_strncmp(str[1], "~", ft_strlen(str[1])) == 0)
			chdir(find_home(envp));
		else if (chdir(str[1]) != 0)
			ft_printf("cd: no such file or directory: %s\n", str[1]);
	}
	else
	{
		errno = 1;
		perror("minishell: ");
		//ft_printf_fd(2, "minishell: command not found: %s\n", str[0]);
	}
	ft_free_matrix((const char **)str, ft_array_len(str));
}

void	ft_pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	ft_printf("%s\n", str);
	free(str);
}

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
}

void	ft_echo(char **comand)
{
	char	**split;
	int		l;

	split = ft_splitn(comand[2], ' ', 2);
	if (ft_strncmp(split[0], "echo", ft_strlen(split[0])) == 0)
	{
		if (split[1][0] == '-' && split[1][1] == 'n')
		{
			l = count_spaces(split[1] + 2);
			ft_printf("%s", split[1] + 2 + l);
		}
		else
			ft_printf("%s\n", split[1]);
	}
	ft_free_matrix((const char **)split, 2);
}

void	ft_unset(char **comand, char **envp)
{
	int		i;
	int		j;
	char	**var;
	char	*aux;

	i = 0;
	var = ft_splitn(comand[2], ' ', 2);
	aux = ft_strjoin(var[1], "=");
	while (envp[i])
	{
		if (ft_strncmp(envp[i], aux, ft_strlen(aux)) == 0)
		{
			j = i;
			while (envp[j])
			{
				envp[j] = envp[j + 1];
				j++;
			}
		}
		else
			i++;
	}
	ft_free_matrix((const char **)var, 2);
	free(aux);
}
