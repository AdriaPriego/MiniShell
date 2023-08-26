/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 20:33:56 by fbosch            #+#    #+#             */
/*   Updated: 2023/08/26 16:54:52 by fbosch           ###   ########.fr       */
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
	if (c == C_VERTICAL_BAR || c == C_LESS || c == C_GREAT || c == C_DOLLAR 
		|| c == C_SINGLE_QUOTE || c == C_DOUBLE_QUOTE)
		return (1);
	return (0);
}