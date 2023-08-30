/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:13:18 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/30 12:52:26 by apriego-         ###   ########.fr       */
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
	if (!aux)
		return (NULL);
	aux[0] = ft_strjoin(GREENBASH, array);
	if (!aux)
		return (ft_free_matrix((const char **)aux, ft_array_len(aux)));
	aux[1] = ft_strjoin(aux[0], "$>");
	if (!aux)
		return (ft_free_matrix((const char **)aux,  ft_array_len(aux)));
	str = ft_strjoin(aux[1], NO_COL);
	if (!aux)
		return (ft_free_matrix((const char **)aux,  ft_array_len(aux)));
	ft_free_matrix((const char **)aux,  ft_array_len(aux));
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
	if (!entry)
	{
		free(aux);
		return (NULL);
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
	if (!args)
		return (NULL);
	args[0] = ft_strdup("/bin/bash");
	if (!args[0])
		return (ft_free_matrix((const char **)args, ft_array_len(args)));
	args[1] = ft_strdup("-c");
	if (!args[1])
		return (ft_free_matrix((const char **)args, ft_array_len(args)));
	args[2] = str;
	args[3] = NULL;
	return (args);
}
