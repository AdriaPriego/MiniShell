/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:02:01 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/08 01:19:29 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_cmd *commands)
{
	int	i;

	i = 0;
	while (commands)
	{
		i++;
		commands = commands->next;
	}
	return (i);
}
void	perror_exit(int exit_code, char *error)
{
	ft_printf_fd(STDERR_FILENO, "minishell: ");
	perror(error);
	exit(exit_code);
}
