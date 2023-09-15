/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:15:02 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/15 13:01:59 by apriego-         ###   ########.fr       */
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

int	valid_comand(char *comand)
{
	int	i;

	i = 0;
	if (ft_isdigit(comand[0]))
		return (1);
	while (comand[i])
	{
		if (ft_isalnum(comand[i]) == 0 && comand[i] != '_')
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

int	ft_strcmp_env(char *env, char *str)
{
	int	i;

	i = 0;
	while (env[i] != '=' && str[i] != '\0')
	{
		if (env[i] != str[i])
			return (env[i] - str[i]);
		i++;
	}
	if (env[i] == '=' && str[i] == '\0')
		return (0);
	return (env[i] - str[i]);
}
