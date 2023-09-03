/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:38:29 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/03 19:22:55 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	> out							"Redirects {empty} to a file called out"
	< out							"It redirects standard input to a file called 'out' if it exists"
	ls |							"Opens std input" // (((("Syntax error"))))
	cat | cat						"Standard input open to write something"
	ls -la <						"Syntax error"
	|								"Syntax error"
	ls | sleep 3 | < dssd			"Executes 3 pipes and throws error for last process {file doesn't exist}"
	ls | sleep 3 | << eof			"Calls here doc and doesn't execute any process until here doc is finished"
	cat << eof < infile				"Open here_doc but uses infile as input for cat"
	< no_file wc -c < out | ls		"First command not executed because no_file doesn't exist, 'ls' executed"

	When it comes to redirections the last parameter is used, the rest of files will be created independently"
*/

int	parser(t_cmd **commands, t_lex **lexer)
{
	int		pipes;
	t_cmd	*new;
	t_lex	*head;

	*commands = NULL;
	if (!lexer)
		return (0);
	if (check_syntax_error(*lexer) == 1)
		return (lexer_lstclear(lexer), 1);
	head = *lexer;
	while (head)
	{
		if (head->token == GREAT || head->token == GREAT_GREAT)
		{

		}
		if (head->token == PIPE)
		{

		}
		head = head->next;
	}
	return (0);
}
