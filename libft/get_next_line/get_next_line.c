/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:27:36 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/14 13:49:29 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_free(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

static char	*ft_get_line(char *tmp)
{
	int		i;
	char	*s;

	i = 0;
	if (!tmp[i])
		return (0);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (tmp[i] == '\n')
		s = malloc(sizeof(char) * (i + 2));
	else
		s = malloc(sizeof(char) * (i + 1));
	if (!s)
		return (0);
	i = 0;
	while (tmp[i] && tmp[i] != '\n')
	{
		s[i] = tmp[i];
		i++;
	}
	if (tmp[i] == '\n')
		s[i++] = '\n';
	s[i] = '\0';
	return (s);
}

static char	*ft_rd_to_tmp(int fd, char *tmp)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
	{
		free(tmp);
		return (0);
	}
	rd_bytes = 1;
	while (!ft_strchr_line(tmp, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
			return (ft_free(tmp, buff));
		if (rd_bytes != 0)
		{
			buff[rd_bytes] = '\0';
			tmp = ft_strjoin_line(tmp, buff);
		}
	}
	free(buff);
	return (tmp);
}

static char	*ft_new_tmp(char *tmp)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (!tmp[i])
	{
		free(tmp);
		return (0);
	}
	s = malloc((ft_len_line(tmp) - i + 1) * sizeof(char));
	if (!s)
	{
		free(tmp);
		return (0);
	}
	j = 0;
	i++;
	while (tmp[i] != '\0')
		s[j++] = tmp[i++];
	s[j] = '\0';
	free(tmp);
	return (s);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*tmp[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	tmp[fd] = ft_rd_to_tmp(fd, tmp[fd]);
	if (!tmp[fd])
		return (0);
	str = ft_get_line(tmp[fd]);
	if (!str)
	{
		free(tmp[fd]);
		tmp[fd] = NULL;
	}
	else
		tmp[fd] = ft_new_tmp(tmp[fd]);
	return (str);
}
