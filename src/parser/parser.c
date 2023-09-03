/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:38:29 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/03 04:42:00 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	> out							"Redirects {empty} to a file called out"
	< out							"It redirects standard input to a file called 'out' if it exists"
	ls |							"Opens std input" // "Syntax error"
	cat | cat						"Standard input open to write something"
	ls -la <						"Syntax error"
	|								"Syntax error"
	ls | sleep 3 | < dssd			"Executes 3 pipes and throws error for last process {file doesn't exist}"
	ls | sleep 3 | << eof			"Calls here doc and doesn't execute any process until here doc is finished"
*/

#define SYNTAX_NL 0
#define SYNTAX_PIPE 1
#define SYNTAX_LESS 2
#define SYNTAX_GREAT 3
#define SYNTAX_LESS_LESS 4
#define SYNTAX_GREAT_GREAT 5



void	parser_error(int error)
{
	ft_printf_fd(STDERR_FILENO, "minishell: ");
	if (error == SYNTAX_NL)
		ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `newline'\n");
	else if (error == SYNTAX_PIPE)
		ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `|'\n");
	else if (error == SYNTAX_LESS)
		ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `<'\n");
	else if (error == SYNTAX_LESS_LESS)
		ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `<<'\n");
	else if (error == SYNTAX_GREAT)
		ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `>'\n");
	else if (error == SYNTAX_GREAT_GREAT)
		ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `>>'\n");
}

int	check_duplicate_tokens(t_lex *lexer)
{
	if (lexer->token == LESS || lexer->token == LESS_LESS
		|| lexer->token == GREAT || lexer->token == GREAT_GREAT)
	{
		if (lexer->next == NULL)
		{
			parser_error(SYNTAX_NL);
			return (1);
		}
		else if (lexer->next->word == NULL)
		{
			if (lexer->next->token == PIPE)
				parser_error(SYNTAX_PIPE);
			else if (lexer->next->token == LESS)
				parser_error(SYNTAX_LESS);
			else if (lexer->next->token == LESS_LESS)
				parser_error(SYNTAX_LESS_LESS);
			else if (lexer->next->token == GREAT)
				parser_error(SYNTAX_GREAT);
			else if (lexer->next->token == GREAT_GREAT)
				parser_error(SYNTAX_GREAT_GREAT);
			return (1);
		}
	}
	return (0);
}

int	check_syntax_error(t_lex *lexer)
{
	while (lexer)
	{
		if (lexer->word == NULL)
		{
			if (check_duplicate_tokens(lexer) == 1)
				return (1);
		}
		lexer = lexer->next;
	}
	return (0);
}

int	parser(t_cmd **commands, t_lex **lexer)
{
	t_cmd	*new;
	t_lex	*head;

	if (!lexer)
	{
		*commands = NULL;
		return (0);
	}
	if (check_syntax_error(*lexer) == 1)
		return (lexer_lstclear(lexer), 1);
	/* head = lexer;
	while (lexer)
	{
		while (lexer->word = NULL && lexer->token )
		new = parser_lstnew();
		if (!new)
			return (1);
		parser_lstadd_back(commands, new);
		lexer = lexer->next;
	} */
	return (0);
}
