/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:01:44 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/22 15:58:24 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    **segment_between_pipes(char **tok, int segment_idx)
{
	int i;
	int j;
	int seg;
	int beg;
	int end;
	char **out;

	i = 0;
	seg = 0;
	beg = 0;
	while (tok[i] && seg < segment_idx)
		if (tok[i++][0] == '|')
			seg++;
	beg = i;
	while (tok[i] && tok[i][0] != '|')
		i++;
	end = i;
	out = ft_calloc(end - beg + 1, sizeof(char *));
	if (!out)
		return (NULL);
	j = 0;
	while (beg < end)
		out[j++] = ft_strdup(tok[beg++]);
	out[j] = NULL;
	return (out);
}

void	execute_pipes(t_central *central, char **split, int pipe_fd[][2], int curr_index, int pipe_amm)
{
	close_unused_pipes(pipe_fd, pipe_amm, curr_index);
	set_pipe_fds(pipe_fd, pipe_amm, curr_index);
	do_cmd(central, segment_between_pipes(split, curr_index));
	exit (central->exit_val);
}

void	piper(t_central *central, char **split, int cmd_count)
{
	int		pipe_fd[cmd_count - 1][2];
	pid_t	pid;
	int		status;
	int		i;

	init_pipes(pipe_fd, cmd_count - 1);
	i = 0;
	while (i < cmd_count)
	{
		pid = fork();
		if (pid == 0)
			execute_pipes(central, split, pipe_fd, i, cmd_count - 1);
		i++;
	}
	close_all_pipes(pipe_fd, cmd_count - 1);
	i = 0;
	while (i < cmd_count)
	{
		waitpid(-1, &status, 0);
		i++;
	}
	central->exit_val = status;
}
