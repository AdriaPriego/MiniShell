/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:16:48 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/17 16:57:22 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	main(void)
{
	char	*entry;
	char	**entry_split;
	int		i;

	entry = getcwd(NULL, 0);
	entry_split = ft_split(entry, '/');
	i = ft_array_len(entry_split);
	ft_printf("%s$>", entry_split[i - 1]);
	while (1)
	{
		
	}
	return(0);
}
