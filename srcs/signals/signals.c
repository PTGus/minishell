/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:23:54 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/29 16:56:02 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ctrl_c(int sig)
{
	(void)sig;
	g_signal = 130;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_d(t_central *central)
{
	clean_all(central);
	printf("exit\n");
	rl_clear_history();
	exit(0);
}

void	handle_signals(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
