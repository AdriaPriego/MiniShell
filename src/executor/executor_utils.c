/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:02:01 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/07 16:26:38 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_return(char *error)
{
	write(2, error, ft_strlen(error));
	exit(EXIT_FAILURE);
}
