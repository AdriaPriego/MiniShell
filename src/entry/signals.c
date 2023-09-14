/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:50:46 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/14 12:18:22 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sig_handler_in_child(int signum)
{
	ft_printf("AAAAAA");
	if (signum == CTRL_C)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == CTRL_SLASH)
		ft_printf("Quit: 3\n");
	exit(0);
}

void	init_signals_in_child(void)
{
	signal(CTRL_C, sig_handler_in_child);
	signal(CTRL_SLASH, sig_handler_in_child);
}

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
	signal(CTRL_C, sig_handler);
	signal(CTRL_SLASH, sig_handler);
}
