/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:41:28 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/21 15:34:34 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "../../includes/types.h"

// PIPES //

// pipe //
void	execute_pipes(t_central *central, t_input *cmd,
			int (*pipe_fd)[2], int curr_index);
void	piper(t_central *central);

#endif
