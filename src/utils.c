/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:15:02 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/08 17:07:19 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*find_home(void)
{
	int	i;

	i = 0;
	while (g_global.env[i])
	{
		if (ft_strncmp(g_global.env[i], "HOME=", ft_strlen("HOME=")) == 0)
			return (g_global.env[i] + ft_strlen("HOME="));
		i++;
	}
	return (NULL);
}

char	**ft_splitn(char *str, char c, int qtt)
{
	char	**array;
	int		i;
	int		j;
	int		k;

	array = malloc((qtt + 1) * sizeof(char *));
	i = 0;
	k = 0;
	while (i < qtt)
	{
		if (str[k] == c)
			k++;
		else
		{
			j = k;
			while ((str[j] != c || i + 1 == qtt) && str[j] != '\0')
				j++;
			array[i] = ft_substr(str, k, j);
			k = j;
			i++;
		}
	}
	array[i] = NULL;
	return (array);
}

int	count_spaces(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0' && str[i] == ' ')
	{
		if (str[i] == ' ')
			count++;
		i++;
	}
	return (count);
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
