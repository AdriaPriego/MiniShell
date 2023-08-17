/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:07:25 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/16 15:52:10 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_test_write_fd(int test, int i)
{
	if (test != -1)
		i += test;
	else
		return (-1);
	return (i);
}

int	ft_printchar_fd(int c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_printstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		i = ft_printstr_fd("(null)", fd);
	else
		i = write(fd, str, ft_strlen(str));
	return (i);
}

int	ft_prints_fd(va_list arg, char c, int fd)
{
	int	writes;

	writes = 0;
	if (c == 'c')
		writes = ft_printchar_fd(va_arg(arg, int), fd);
	else if (c == 's')
		writes = ft_printstr_fd(va_arg(arg, char *), fd);
	else if (c == 'p')
		writes = ft_printpnt_fd(va_arg(arg, unsigned long), fd);
	else if (c == 'd' || c == 'i')
		writes = ft_printnbr_fd(va_arg(arg, int), fd);
	else if (c == 'u')
		writes = ft_printunnbr_fd(va_arg(arg, unsigned int), 0, fd);
	else if (c == 'x')
		writes = ft_printundhex_fd(va_arg(arg, unsigned int), 0, fd);
	else if (c == 'X')
		writes = ft_printuphex_fd(va_arg(arg, unsigned int), 0, fd);
	else if (c == '%')
		writes = ft_printchar_fd('%', fd);
	return (writes);
}

int	ft_printf_fd(const int fd, const char *str, ...)
{
	int		i;
	va_list	arg;
	int		print_length;
	int		aux;

	i = 0;
	print_length = 0;
	va_start(arg, str);
	while (str[i] && print_length != -1)
	{
		if (str[i] == '%')
		{
			aux = ft_prints_fd(arg, str[i + 1], fd);
			if (aux != -1)
				print_length += aux;
			else
				print_length = aux;
			i++;
		}
		else
			print_length += ft_printchar_fd(str[i], fd);
		i++;
	}
	va_end(arg);
	return (print_length);
}
