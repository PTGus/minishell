/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:01:44 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/28 15:39:12 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**segment_between_pipes(char **tok, int segment_idx)
{
	int		i;
	int		j;
	int		seg;
	int		beg;
	int		end;
	char	**out;

	i = 0;
	seg = 0;
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
	i = beg;
	while (i < end)
	{
		if (!ft_strcmp(tok[i], "<") || !ft_strcmp(tok[i], ">")
			|| !ft_strcmp(tok[i], ">>") || !ft_strcmp(tok[i], "<<"))
			i += 2; // skip redirection and its target
		else
			out[j++] = ft_strdup(tok[i++]);
	}
	out[j] = NULL;
	return (out);
}


void	execute_pipes(t_central *central, char **split, \
			int (*pipe_fd)[2], int curr_index, int pipe_amm)
{
	reset_fds(1);
	close_unused_pipes(pipe_fd, pipe_amm, curr_index);
	has_to_redirect(central, split);
	set_pipe_fds(pipe_fd, pipe_amm, curr_index);
	do_cmd(central, segment_between_pipes(split, curr_index));
	reset_fds(1);
	exit (central->exit_val);
}

void	piper(t_central *central, char **split, int cmd_count)
{
	int		(*pipe_fd)[2];
	pid_t	pid;
	int		status;
	int		i;

	pipe_fd = malloc(sizeof(int [2]) * cmd_count - 1);
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
	free(pipe_fd);
}
