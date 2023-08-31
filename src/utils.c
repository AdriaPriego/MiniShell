/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:15:02 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/24 14:53:23 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*find_home(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "HOME=", ft_strlen("HOME=")) == 0)
			return (envp[i] + ft_strlen("HOME="));
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
