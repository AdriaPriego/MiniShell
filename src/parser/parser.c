/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:38:29 by fbosch            #+#    #+#             */
/*   Updated: 2023/08/31 21:35:42 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*parser(t_cmd **commands, t_lex *lexer)
{
	t_cmd	*new;
	t_lex	*head;

	(void)commands;
	head = lexer;
	while (lexer)
	{
		new = malloc(sizeof(t_cmd));
		if (lexer->word == NULL)
			printf ("a\n");
		lexer = lexer->next;
	}	
	return (0);
}
