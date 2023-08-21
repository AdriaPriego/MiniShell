/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:16:48 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/21 18:15:34 by apriego-         ###   ########.fr       */
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

void	generate_entry(void)
{
	char	*entry;
	char	**entry_split;
	int		i;

	entry = getcwd(NULL, 0);
	entry_split = ft_split(entry, '/');
	free(entry);
	i = ft_array_len(entry_split);
	entry = entry_split[i - 1];
	ft_printf("%s", GREENBASH);
	ft_printf("%s$> ", entry);
	ft_printf("%s", NO_COL);
	ft_free_matrix((const char**)entry_split, i);
}

char	*parse_command(const char *s1)
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
	args[2] = parse_command(str);
	args[3] = NULL;
	return (args);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf("\n");
		generate_entry();
	}
}

int	main(void)
{
	char	*str;
	char	**str1;
	pid_t	pid;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	generate_entry();
	str = get_next_line(STDIN_FILENO);
	while (str && ft_strncmp(str, "exit\n", ft_strlen(str)) != 0)
	{
		str1 = generate(str);
		free(str);
		pid = fork();
		if (pid == 0)
			execve("/bin/bash", str1, NULL);
		wait(0);
		ft_free_matrix((const char**)str1, 3);
		generate_entry();
		str = get_next_line(STDIN_FILENO);
	}
	free(str);
	return (0);
}
