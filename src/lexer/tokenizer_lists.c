/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_lists.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 20:34:14 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/06 18:00:51 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_lex	*lexer_lstnew(void)
{
	t_lex	*node;

	node = malloc(sizeof(t_lex));
	if (!node)
		return (NULL);
	node->word = NULL;
	node->token = NONE;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	lexer_lstadd_back(t_lex **lst, t_lex *new)
{
	t_lex	*last;

	if ((*lst))
	{
		last = lexer_lstlast(*lst);
		last->next = new;
		new->prev = last;
	}
	else
		(*lst) = new;
}

void	lexer_lstclear(t_lex **lst)
{
	t_lex	*nxt;
	t_lex	*aux;

	aux = *lst;
	while (aux)
	{
		nxt = aux->next;
		free(aux->word);
		free(aux);
		aux = nxt;
	}
	*lst = NULL;
}

int	lexer_lstsize(t_lex *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_lex	*lexer_lstlast(t_lex *lst)
{
	t_lex	*node;

	if (!lst)
		return (0);
	node = lst;
	while ((node->next))
		node = node->next;
	return (node);
}
