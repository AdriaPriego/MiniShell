/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:25:42 by apriego-          #+#    #+#             */
/*   Updated: 2023/07/11 18:11:34 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*var;

	i = ft_strlen(s1) + 1;
	var = malloc(i * sizeof(char));
	if (!var)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		var[i] = s1[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}
