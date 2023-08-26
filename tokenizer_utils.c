/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 20:33:56 by fbosch            #+#    #+#             */
/*   Updated: 2023/08/26 23:40:19 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_isreserved(int c)
{
	if (c == C_VERTICAL_BAR || c == C_LESS || c == C_GREAT || c == C_DOLLAR
		|| c == C_SINGLE_QUOTE || c == C_DOUBLE_QUOTE)
		return (1);
	return (0);
}

void	print_tokens(t_lex *lexer)
{
	while (lexer)
	{
		if (!lexer->word)
		{
			if (lexer->token == PIPE)
				printf(" PIPE");
			else if (lexer->token == LESS)
				printf(" LESS");
			else if (lexer->token == LESS_LESS)
				printf(" LESS_LESS");
			else if (lexer->token == GREAT)
				printf(" GREAT");
			else if (lexer->token == GREAT_GREAT)
				printf(" GREAT_GREAT");
			else if (lexer->token == SINGLE_QUOTE)
				printf(" SINGLE_QUOTE");
			else if (lexer->token == DOUBLE_QUOTE)
				printf(" DOUBLE_QUOTE");
		}
		else
			printf(" %s ", lexer->word);
		lexer = lexer->next;
	}
}
