/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:32:23 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/13 18:20:14 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	ft_isspace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
		|| str[i] == '\n' || str[i] == '\v' || str[i] == '\f')
		i++;
	return (i);
}

int	ft_test_int(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	result = 0;
	sign = 1;
	i = ft_isspace(str);
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result * sign > (LLONG_MAX - (str[i] - '0')) / 10 || result
			* sign < (LLONG_MIN + (str[i] - '0')) / 10)
			return (-1);
		result *= 10;
		result += (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' && ft_isspace(str + i) == 0)
		return (-1);
	return (0);
}
