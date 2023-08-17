/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:07:25 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/16 15:52:57 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_test_write(int test, int i)
{
	if (test != -1)
		i += test;
	else
		return (-1);
	return (i);
}

int	ft_printchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_printstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		i = ft_printstr("(null)");
	else
		i = write(1, str, ft_strlen(str));
	return (i);
}

int	ft_prints(va_list arg, char c)
{
	int	writes;

	writes = 0;
	if (c == 'c')
		writes = ft_printchar(va_arg(arg, int));
	else if (c == 's')
		writes = ft_printstr(va_arg(arg, char *));
	else if (c == 'p')
		writes = ft_printpnt(va_arg(arg, unsigned long));
	else if (c == 'd' || c == 'i')
		writes = ft_printnbr(va_arg(arg, int));
	else if (c == 'u')
		writes = ft_printunnbr(va_arg(arg, unsigned int), 0);
	else if (c == 'x')
		writes = ft_printundhex(va_arg(arg, unsigned int), 0);
	else if (c == 'X')
		writes = ft_printuphex(va_arg(arg, unsigned int), 0);
	else if (c == '%')
		writes = ft_printchar('%');
	return (writes);
}

int	ft_printf(const char *str, ...)
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
			aux = ft_prints(arg, str[i + 1]);
			if (aux != -1)
				print_length += aux;
			else
				print_length = aux;
			i++;
		}
		else
			print_length += ft_printchar(str[i]);
		i++;
	}
	va_end(arg);
	return (print_length);
}
