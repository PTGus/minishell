/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:49:56 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/10 16:54:39 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_all_pipes(int (*pipe_fd)[2], int pipe_amm)
{
	int	i;

	i = 0;
	while (i < pipe_amm)
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		i++;
	}
}

void	set_pipe_fds(int (*pipe_fd)[2], int pipe_count, int idx)
{
	if (idx > 0)
	{
		dup2(pipe_fd[idx - 1][0], STDIN_FILENO);
		close(pipe_fd[idx - 1][0]);
	}
	if (idx < pipe_count)
	{
		dup2(pipe_fd[idx][1], STDOUT_FILENO);
		close(pipe_fd[idx][1]);
	}
}

void	close_unused_pipes(int (*pipe_fd)[2], int pipe_count, int idx)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (i != idx - 1)
			close(pipe_fd[i][0]);
		if (i != idx)
			close(pipe_fd[i][1]);
		i++;
	}
}

void	init_pipes(int (*pipe_fd)[2], int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (pipe(pipe_fd[i]) == -1)
		{
			perror("pipe");
			exit(1);
		}
		i++;
	}
}

int	to_pipe(t_central *central)
{
	if (central->matrix_len > 1)
	{
		if (handle_all_heredocs(central) == 130)
			return (130);
		piper(central);
		free_heredoc_paths(central);
		return (0);
	}
	return (1);
}
