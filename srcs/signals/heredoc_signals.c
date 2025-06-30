/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:10:36 by gumendes          #+#    #+#             */
/*   Updated: 2025/06/26 09:28:18 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	heredoc_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
	g_signal = 130;
}

{
// Call this before reading your heredoc lines
void	setup_heredoc_signals(void)
	struct sigaction sa;

	sa.sa_handler = &heredoc_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
