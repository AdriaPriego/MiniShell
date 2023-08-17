/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfnbr_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:32:16 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/16 11:11:48 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printnbr_fd(int n, int fd)
{
	char	*num;
	int		writed;

	num = ft_itoa(n);
	if (!num)
		return (-1);
	writed = ft_printstr_fd(num, fd);
	free(num);
	return (writed);
}

int	ft_printunnbr_fd(unsigned int num, int test, int fd)
{
	int	i;

	i = 0;
	if (num >= 10 && test != -1 && i != -1)
	{
		test = ft_printunnbr_fd(num / 10, test, fd);
		i = ft_test_write_fd(test, i);
		if (i == -1)
			return (i);
		test = ft_printunnbr_fd(num % 10, test, fd);
		i = ft_test_write_fd(test, i);
		if (i == -1)
			return (i);
	}
	else
	{
		test = ft_printchar_fd(num + '0', fd);
		i = ft_test_write_fd(test, i);
	}
	return (i);
}
