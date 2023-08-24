/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:16:48 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/24 14:53:35 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// SEGURAMENTE COMAND[2] SE DEBE DE CANVIAR SI SE CANVIA 
// COMO SE GUARDAN LAS COMANDAS

static void	execute_comand(char **comand, char **envp, pid_t pid)
{
	if (ft_strnstr(comand[2], "cd", ft_strlen(comand[2])) != 0)
	{
		if (pid != 0)
			ft_cd(comand, envp);
	}
	else if (pid == 0)
	{
		if (ft_strncmp(comand[2], "pwd", ft_strlen(comand[2])) == 0)
			ft_pwd();
		else if (ft_strncmp(comand[2], "env", ft_strlen(comand[2])) == 0)
			ft_env(envp);
		else if (ft_strnstr(comand[2], "echo", ft_strlen(comand[2])) != 0)
			ft_echo(comand);
		else
			execve("/bin/bash", comand, envp);
	}
}

static void	generate_terminal(char **envp)
{
	char	*str;
	char	**comand;
	pid_t	pid;

	str = generate_entry(envp);
	while (str && (ft_strncmp(str, "exit", ft_strlen(str)) != 0
			|| ft_strlen(str) == 0))
	{
		add_history(str);
		comand = generate(str);
		pid = fork();
		execute_comand(comand, envp, pid);
		if (pid == 0)
			return ;
		wait(0);
		ft_free_matrix((const char **)comand, 3);
		str = generate_entry(envp);
	}
	if (!str || !ft_strncmp(str, "exit", ft_strlen(str)))
		ft_printf("exit\n");
	free(str);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init_signals();
	generate_terminal(envp);
	return (0);
}
