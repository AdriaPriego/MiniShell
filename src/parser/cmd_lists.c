/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_lists.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:32:11 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/03 18:53:22 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parser_lstnew(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->args = NULL;
	node->redirect = NULL;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	parser_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if ((*lst))
	{
		last = parser_lstlast(*lst);
		last->next = new;
		new->prev = last;
	}
	else
		(*lst) = new;
}

void	parser_lstclear(t_cmd **lst)
{
	t_cmd	*temp;
	t_cmd	*aux;

	aux = *lst;
	while (aux)
	{
		temp = aux->next;
		ft_free_malloc_array(aux->args, ft_array_len(aux->args));
		//free redirect structure
		free(aux);
		aux = temp;
	}
	*lst = NULL;
}

int	parser_lstsize(t_cmd *lst)
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

t_cmd	*parser_lstlast(t_cmd *lst)
{
	t_cmd	*node;

	if (!lst)
		return (0);
	node = lst;
	while ((node->next))
		node = node->next;
	return (node);
}
