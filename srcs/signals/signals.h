/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:50:28 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/21 16:36:40 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "../../includes/types.h"

// SIGNALS //

// heredoc_signals //
void	setup_heredoc_signals(void);
void	restore_term(void);

// signals //
void	ctrl_c(int sig);
void	ctrl_d(void);
void	handle_signals(void);
void	treat_status(t_central *central, int status);

#endif
