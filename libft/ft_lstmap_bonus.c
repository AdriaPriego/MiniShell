/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:55:55 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/25 15:51:12 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*def;
	t_list	*auxdef;

	if (!lst)
		return (0);
	def = malloc(sizeof(t_list));
	if (!def)
		return (0);
	auxdef = def;
	while (lst)
	{
		auxdef->content = f(lst->content);
		if (!auxdef)
			ft_lstclear(&lst, del);
		lst = lst->next;
		if (lst)
		{
			auxdef->next = malloc(sizeof(t_list));
			auxdef = auxdef->next;
		}
		else
			auxdef->next = 0;
	}
	return (def);
}
