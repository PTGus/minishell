/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:01:44 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/10 16:55:14 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_pipes(t_central *central, t_input *cmd,
			int (*pipe_fd)[2], int curr_index)
{
	central->curr_cmd_idx = curr_index;
	central->curr_heredoc_idx = 0;
	set_pipe_fds(pipe_fd, central->matrix_len - 1, curr_index);
	close_unused_pipes(pipe_fd, central->matrix_len - 1, curr_index);
	if (has_to_redirect(central, cmd) != 0)
		exit(central->exit_val);
	do_cmd(central, cmd);
	reset_fds(1);
	exit(central->exit_val);
}

void	piper(t_central *central)
{
	int		(*pipe_fd)[2];
	pid_t	*pid;
	int		status;
	int		i;

	pipe_fd = malloc(sizeof(int [2]) * (central->matrix_len - 1));
	pid = malloc(sizeof(pid_t) * central->matrix_len);
	init_pipes(pipe_fd, central->matrix_len - 1);
	i = -1;
	while (++i < central->matrix_len)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			execute_pipes(central, central->cmd[i], pipe_fd, i);
			exit(central->exit_val);
		}
	}
	close_all_pipes(pipe_fd, central->matrix_len - 1);
	i = -1;
	while (++i < central->matrix_len)
		waitpid(pid[i], &status, 0);
	central->exit_val = (status >> 8) & 0xFF;
	return (free(pid), free(pipe_fd), (void) 0);
}
