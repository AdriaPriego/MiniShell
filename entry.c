/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:13:18 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/23 17:57:06 by apriego-         ###   ########.fr       */
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

char	*generate_entry(void)
{
	char	*entry[4];
	char	**entry_split;
	char	*str;
	int		i;

	entry[0] = getcwd(NULL, 0);
	entry_split = ft_split(entry[0], '/');
	free(entry[0]);
	i = ft_array_len(entry_split);
	entry[0] = entry_split[i - 1];
	entry[1] = ft_strjoin(GREENBASH, entry_split[i - 1]);
	entry[2] = ft_strjoin(entry[1], "$>");
	entry[3] = ft_strjoin(entry[2], NO_COL);
	str = readline(entry[3]);
	ft_free_matrix((const char **)entry_split, i);
	free(entry[1]);
	free(entry[2]);
	free(entry[3]);
	return (str);
}

char	**generate(char *str)
{
	char	**args;

	args = malloc(4 * sizeof(char *));
	args[0] = ft_strdup("/bin/bash");
	args[1] = ft_strdup("-c");
	args[2] = str;
	args[3] = NULL;
	return (args);
}
