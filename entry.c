/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:13:18 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/24 14:53:08 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	*ft_joincolors(char *array)
{
	char	**aux;
	char	*str;

	aux = malloc(2 * sizeof(char *));
	aux[0] = ft_strjoin(GREENBASH, array);
	aux[1] = ft_strjoin(aux[0], "$>");
	str = ft_strjoin(aux[1], NO_COL);
	ft_free_matrix((const char **)aux, 2);
	return (str);
}

char	*generate_entry(char **envp)
{
	char	*entry;
	char	*aux;
	char	*split;
	char	*str;

	aux = getcwd(NULL, 0);
	if (ft_strncmp(aux, find_home(envp), ft_strlen(aux)) == 0)
		entry = ft_joincolors("~");
	else if (ft_strncmp(aux, "/", ft_strlen(aux)) == 0)
		entry = ft_joincolors(aux);
	else
	{
		split = ft_strrchr(aux, '/');
		entry = ft_joincolors(split + 1);
	}
	str = readline(entry);
	free(aux);
	free(entry);
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
