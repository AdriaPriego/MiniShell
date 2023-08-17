/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 22:51:52 by apriego-          #+#    #+#             */
/*   Updated: 2023/05/04 13:40:39 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	i = 0;
	dlen = 0;
	slen = 0;
	while (dest[dlen] != '\0' && dlen < size)
		dlen++;
	while (src[slen] != '\0')
		slen++;
	while (src[i] != '\0' && i < size - dlen - 1 && dlen < size)
	{
		dest[dlen + i] = src[i];
		i++;
	}
	if (i > 0)
		dest[dlen + i] = '\0';
	return (dlen + slen);
}
