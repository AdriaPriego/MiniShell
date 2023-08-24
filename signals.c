/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:50:46 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/24 11:00:21 by apriego-         ###   ########.fr       */
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
	if (signum == CTRL_SLASH)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	init_signals(void)
{
	rl_catch_signals = 0;
	signal(CTRL_C, sig_handler);
	signal(CTRL_SLASH, sig_handler);
}
