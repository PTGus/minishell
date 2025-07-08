/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:50:28 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/08 10:51:34 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

// SIGNALS //

// heredoc_signals //
void	setup_heredoc_signals(void);

// signals //
void	ctrl_c(int sig);
void	ctrl_d(void);
void	handle_signals(void);

#endif
