/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:49:56 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/21 17:21:12 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_all_pipes(int pipe_fd[][2], int pipe_amm)
{
	
}

void	set_pipe_fds(int pipe_fd[][2], int pipe_amm, int current_index)
{
	if (current_index == 0)
	{
		dup2(pipe_fd[0][1], STDOUT_FILENO);
		return ;
	}
	else if (current_index == pipe_amm - 1)
	{
		dup2(pipe_fd[current_index - 1][0], STDIN_FILENO);
		return ;
	}
	dup2(pipe_fd[current_index - 1][0], STDIN_FILENO);
	dup2(pipe_fd[current_index][1], STDOUT_FILENO);
}

void	close_unused_pipes(int pipe_fd[][2], int pipe_amm, int current_index)
{
	int	i;

	i = 0;
	while (i < pipe_amm)
	{
		if (current_index == 0 && i == 0)
			close(pipe_fd[i][0]);
		if (current_index == pipe_amm - 1 && i == current_index)
			close(pipe_fd[i][1]);
		if (i != current_index - 1)
			close(pipe_fd[i][0]);
		if (i != current_index)
			close(pipe_fd[i][1]);
		i++;
	}
}

void init_pipes(int pipe_fd[][2], int pipe_amm)
{
	int i;

	i = 0;
	while (i < pipe_amm)
	{
		if (pipe(pipe_fd[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

int	to_pipe(t_central *central, char **split)
{
	int	i;
	int	pipe_amm;

	i = 0;
	pipe_amm = 0;
	while (split[i])
	{
		if (ft_strcmp(split[i], "|") == 0)
			pipe_amm++;
		i++;
	}
	if (pipe_amm > 0)
	{
		piper(central, split, pipe_amm + 1);
		return(0);
	}
	return (i);
}
