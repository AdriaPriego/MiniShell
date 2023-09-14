/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:15:02 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/14 13:42:11 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*find_home(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", ft_strlen("HOME=")) == 0)
			return (env[i] + ft_strlen("HOME="));
		i++;
	}
	return (NULL);
}


int	valid_command(char *command)
{
	int	i;

	i = 0;
	if (ft_isdigit(command[0]))
		return (1);
	while (command[i])
	{
		if (ft_isalnum(command[i]) == 0 && command[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*str1;

	i = 0;
	str = (unsigned char *)s1;
	str1 = (unsigned char *)s2;
	while ((str[i] != '\0' || str1[i] != '\0'))
	{
		if (str[i] != str1[i])
			return (str[i] - str1[i]);
		i++;
	}
	return (0);
}

void	ft_print_export(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		ft_printf("declare -x %s\n", matrix[i++]);
}

int	contain_env(char **env, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], str, ft_strlen_chr(env[i], '=')) == 0)
			return (0);
		i++;
	}
	return (1);
}