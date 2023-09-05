/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:13:18 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/05 12:41:33 by apriego-         ###   ########.fr       */
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

void	generate_terminal(char **envp)
{
	t_lex	*lexer;
	char	*str;

	str = generate_entry(envp);
	if (!str)
		return ;
	while (str && (ft_strnstr(str, "exit", ft_strlen(str)) == 0
			|| ft_strlen(str) == 0))
	{
		add_history(str);
		tokenizer(str, &lexer);
		expansor(&lexer, envp);
		ft_optimize_expan(&lexer);
		printf("entry: %s\n", str);
		printf("token: ");
		print_tokens(lexer);
		printf("\n");
		free(str);
		lexer_lstclear(&lexer);
		str = generate_entry(envp);
		if (!str)
			return ;
	}
	if (!str || !ft_strncmp(str, "exit", ft_strlen(str)))
		ft_printf("exit\n");
	free(str);
}
