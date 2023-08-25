/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:16:48 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/25 17:53:42 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_isspace(int	c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v'|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_isreserved(int	c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	create_token(char *str, int i, t_lex *lexer)
{
	t_lex *new;

	new = lexer_lstnew();
	if (!new)
		return (-1);
	if (ft_isreserved(str[i]))
	{
		if (str[i] == '|')
			new->token = PIPE;
	}
	while (str[i] != '\0' || !ft_isspace(str[i]) || !ft_isreserved(str[i]))
	{
		
	}
}
int	tokenizer(char *str)
{
	t_lex	*lexer;
	int		i;

	lexer = NULL;
	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]) && !ft_isreserved(str[i]))
			create_token(str, &i, lexer);
		else if (!ft_isspace(str[i]) && ft_isreserved(str[i]))
			create_token(str, &i, lexer);
		else
			i++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	tokenizer(av[1]);
}
