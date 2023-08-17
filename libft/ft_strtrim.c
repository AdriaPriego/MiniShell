/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:47:20 by apriego-          #+#    #+#             */
/*   Updated: 2023/05/08 17:55:53 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_getstart(const char *str, const char *set)
{
	int	len;
	int	i;
	int	ext;

	ext = 0;
	len = ft_strlen(str);
	i = 0;
	while (i < len && ext == 0)
	{
		if (ft_strchr(set, str[i]) == 0)
			ext = 1;
		else
			i++;
	}
	return (i);
}

int	ft_getend(const char *str, const char *set)
{
	int	len;
	int	i;
	int	ext;

	ext = 0;
	len = ft_strlen(str);
	i = 0;
	while (i < len && ext == 0)
	{
		if (ft_strrchr(set, str[len - i - 1]) == 0)
			ext = 1;
		else
			i++;
	}
	return (len - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*newstr;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	start = ft_getstart(s1, set);
	end = ft_getend(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	newstr = (char *)malloc(sizeof(char) * (end - start + 1));
	if (newstr == NULL)
		return (NULL);
	ft_strlcpy(newstr, s1 + start, end - start + 1);
	return (newstr);
}
