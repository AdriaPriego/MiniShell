/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:44:02 by apriego-          #+#    #+#             */
/*   Updated: 2023/05/08 14:06:25 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*nxt;
	t_list	*aux;

	aux = *lst;
	while (aux)
	{
		nxt = aux->next;
		del(aux->content);
		free(aux);
		aux = nxt;
	}
	*lst = 0;
}
