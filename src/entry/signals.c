/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:50:46 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/08 13:01:26 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	sig_handler(int signum)
{
	if (signum == CTRL_C)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_signals(void)
{
	rl_catch_signals = 0;
	//signal(CTRL_C, sig_handler);
	signal(CTRL_SLASH, sig_handler);
}
