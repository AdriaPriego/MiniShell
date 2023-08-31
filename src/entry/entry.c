/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:13:18 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/31 13:15:19 by apriego-         ###   ########.fr       */
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
		return ((char *)ft_free_matrix((const char **)aux, ft_array_len(aux)));
	aux[1] = ft_strjoin(aux[0], "$>");
	if (!aux)
		return ((char *)ft_free_matrix((const char **)aux,  ft_array_len(aux)));
	str = ft_strjoin(aux[1], NO_COL);
	if (!str)
		return ((char *)ft_free_matrix((const char **)aux,  ft_array_len(aux)));
	ft_free_matrix((const char **)aux,  2);
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

// SEGURAMENTE COMAND[2] SE DEBE DE CANVIAR SI SE CANVIA
// COMO SE GUARDAN LAS COMANDAS

int	execute_comand(char **comand, char **envp)
{
	pid_t	pid;

	if (ft_strlen(comand[2]) == 0)
		return (EXIT_DAD);
	else if (ft_strnstr(comand[2], "cd", ft_strlen(comand[2])) != 0)
		ft_cd(comand, envp);
	else if (ft_strnstr(comand[2], "env", ft_strlen(comand[2])) != 0)
		ft_env(envp);
	else if (ft_strnstr(comand[2], "pwd", ft_strlen(comand[2])) != 0)
		ft_pwd();
	else if (ft_strnstr(comand[2], "echo", ft_strlen(comand[2])) != 0)
		ft_echo(comand);
	else if (ft_strnstr(comand[2], "unset", ft_strlen(comand[2])) != 0)
		ft_unset(comand, envp);
	else if (ft_strnstr(comand[2], "export", ft_strlen(comand[2])) != 0)
		ft_export(comand, envp);
	else
	{
		pid = fork();
		if (pid == 0)
			execve("/bin/bash", comand, envp);
		wait(0);
	}
	return (EXIT_DAD);
}

void	generate_terminal(char **envp)
{
	char	*str;
	char	**comand;

	str = generate_entry(envp);
	if (!str)
		return ;
	while (str && (ft_strnstr(str, "exit", ft_strlen(str)) == 0
			|| ft_strlen(str) == 0))
	{
		add_history(str);
		//COMAND COSA GUARRA
		comand = generate(str);
		if (execute_comand(comand, envp) == EXIT_SON)
			return ;
		ft_free_matrix((const char **)comand, 3);
		str = generate_entry(envp);
		if (!str)
			return ;
	}
	if (!str || !ft_strncmp(str, "exit", ft_strlen(str)))
		ft_printf("exit\n");
	free(str);
}
