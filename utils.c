/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:48:46 by fbosch            #+#    #+#             */
/*   Updated: 2023/08/25 17:50:20 by fbosch           ###   ########.fr       */
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
	node->next = NULL;
	return (node);
}

void	lexer_lstadd_back(t_lex **lst, t_lex *new)
{
	if ((*lst))
		lexer_lstlast(*lst)->next = new;
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
