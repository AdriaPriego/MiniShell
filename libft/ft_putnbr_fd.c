/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:28:25 by apriego-          #+#    #+#             */
/*   Updated: 2023/05/08 12:25:56 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int	ft_calc10(int n)
{
	int	qtt10;
	int	ext;

	ext = 0;
	qtt10 = 1;
	while (qtt10 <= n && ext == 0)
	{
		if (qtt10 < 1000000000)
			qtt10 *= 10;
		else
			ext = 1;
	}
	if (ext == 0 && n != 0)
		qtt10 = qtt10 / 10;
	return (qtt10);
}

static int	ft_isnegative(int *n)
{
	int	neg;

	if (*n < 0 && *n != -2147483648)
	{
		*n *= -1;
		neg = 1;
	}
	else
		neg = 0;
	return (neg);
}

static void	ft_min_int(int n, int fd)
{
	int		qtt10;
	char	c;

	if (n == -2147483648)
	{
		qtt10 = 1000000000;
		write(fd, "-", 1);
		while (qtt10 >= 1)
		{
			c = (((n / qtt10) * -1) + '0');
			write(fd, &c, 1);
			n = n % qtt10;
			qtt10 = qtt10 / 10;
		}
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int		qtt10;
	int		neg;
	char	c;

	if (n == -2147483648)
		ft_min_int(n, fd);
	else
	{
		neg = ft_isnegative(&n);
		qtt10 = ft_calc10(n);
		if (neg == 1)
			write(fd, "-", 1);
		while (qtt10 >= 1)
		{
			c = ((n / qtt10) + '0');
			write(fd, &c, 1);
			n = n % qtt10;
			qtt10 = qtt10 / 10;
		}
	}
}
