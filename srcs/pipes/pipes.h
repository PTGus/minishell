/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:41:28 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/08 10:49:36 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
#define PIPES_H

// PIPES //

// pipe //
void	execute_pipes(t_central *central, t_input *cmd, \
	int (*pipe_fd)[2], int curr_index);
void	piper(t_central *central);

#endif
