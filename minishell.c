/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:16:48 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/17 19:06:42 by apriego-         ###   ########.fr       */
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

char	*cosa(const char *s1)
{
	int		i;
	char	*var;

	i = ft_strlen(s1) + 1;
	var = malloc(i * sizeof(char));
	if (!var)
		return (0);
	i = 0;
	while (s1[i] != '\n')
	{
		var[i] = s1[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

char	**generate(char *str)
{
	char	**args;

	args = malloc(4 * sizeof(char *));
	args[0] = ft_strdup("/bin/bash");
	args[1] = ft_strdup("-c");
	args[2] = cosa(str);
	args[3] = NULL;
	return (args);
}

int	main(int ac, char **av, char **env)
{
	char	*entry;
	char	**entry_split;
	char	*str;
	char	**str1;
	int		i;

	ac = 0;
	av = env;
	env = av;
	ft_printf("%s", env[0]);
	ft_printf("%s", env[1]);
	ft_printf("%s", env[2]);
	ft_printf("%s", env[3]);
	ft_printf("%s", env[4]);
	entry = getcwd(NULL, 0);
	entry_split = ft_split(entry, '/');
	i = ft_array_len(entry_split);
	ft_printf("%s", GREENBASH);
	ft_printf("%s$>", entry_split[i - 1]);
	ft_printf("%s", NO_COL);
	str = get_next_line(STDIN_FILENO);
	while (ft_strncmp(str, "exit\n", ft_strlen(str)) != 0)
	{
		str1 = generate(str);
		execve("/bin/bash", str1, NULL);
		ft_printf("%s", GREENBASH);
		ft_printf("%s$>", entry_split[i - 1]);
		ft_printf("%s", NO_COL);
		str = get_next_line(STDIN_FILENO);
		printf("%s", str);
	}
	return (0);
}
