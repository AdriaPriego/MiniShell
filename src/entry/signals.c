/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:50:46 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/15 17:42:09 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	sig_handler_def(int signum)
{
	if (signum == CTRL_C)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	sig_handler_childs(int signum)
{
	if (signum == CTRL_C)
	{
		ft_printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
	}
}

int	init_signals(int mode)
{
	if (mode == DEFAULT)
		signal(CTRL_C, sig_handler_def);
	else if (mode == CHILDS)
		signal(CTRL_C, sig_handler_childs);
	signal(CTRL_SLASH, sig_handler_def);
	return (1);
}
