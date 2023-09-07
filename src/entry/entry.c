/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:13:18 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/07 21:58:04 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		return ((char *)ft_free_matrix((const char **)aux, ft_array_len(aux)));
	str = ft_strjoin(aux[1], NO_COL);
	if (!str)
		return ((char *)ft_free_matrix((const char **)aux, ft_array_len(aux)));
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
	if (ft_strcmp(find_home(envp), aux) == 0)
		entry = ft_joincolors("~");
	else if (ft_strcmp(aux, "/") == 0)
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

int	string_to_command(char *str, t_cmd **commands, char **env)
{
	int		status;
	t_lex	*lexer;

	(void)env;
	lexer = NULL;
	*commands = NULL;
	status = tokenizer(str, &lexer);
	if (status == 0)
		status = expansor(&lexer, env);
	if (status == 0)
		status = parser(commands, &lexer);
	print_commands(*commands);
	if (status == 1)
		ft_printf_fd(STDERR_FILENO, MSSG_MEMORY_ERROR);
	lexer_lstclear(&lexer);
	return (status);
}

void	generate_terminal(char **envp)
{
	t_cmd	*commands;
	char	*str;

	str = generate_entry(envp);
	while (str && (ft_strnstr(str, "exit", ft_strlen(str)) == 0
			|| ft_strlen(str) == 0))
	{
		add_history(str);
		if (string_to_command(str, &commands, envp) == 0 && commands != NULL)
		{
			execute_commands(commands, envp);
		}
		parser_lstclear(&commands);
		free (str);
		str = generate_entry(envp);
	}
	if (!str || !ft_strncmp(str, "exit", ft_strlen(str)))
		ft_printf("exit\n");
	free(str);
}
