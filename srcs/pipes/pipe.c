/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:01:44 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/31 14:54:51 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_pipes(t_central *central, t_input *cmd,
			int (*pipe_fd)[2], pid_t *pid)
{
	central->curr_hdc_idx = 0;
	set_pipe_fds(pipe_fd, central->matrix_len - 1, central->curr_cmd_idx);
	close_unused_pipes(pipe_fd, central->matrix_len - 1, central->curr_cmd_idx);
	if (has_to_redirect(central, cmd) != 0)
		exit(central->exit_val);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	free(pipe_fd);
	free(pid);
	rl_clear_history();
	do_cmd(central, cmd);
	clean_all(central);
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
			central->curr_cmd_idx = i;
			execute_pipes(central, central->cmd[i], pipe_fd, pid);
			exit(central->exit_val);
		}
	}
	close_all_pipes(pipe_fd, central->matrix_len - 1);
	i = -1;
	signal(SIGINT, SIG_IGN);
	while (++i < central->matrix_len)
		waitpid(pid[i], &status, 0);
	return (treat_status(central, status), free(pid), free(pipe_fd), (void) 0);
}
