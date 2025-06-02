/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:01:44 by gumendes          #+#    #+#             */
/*   Updated: 2025/06/02 10:36:55 by gumendes         ###   ########.fr       */
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
			i += 2;
		else
			out[j++] = ft_strdup(tok[i++]);
	}
	out[j] = NULL;
	return (out);
}

char	**segment_full(char **tok, int segment_idx)
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
		out[j++] = ft_strdup(tok[i++]);
	out[j] = NULL;
	return (out);
}

void	execute_pipes(t_central *central, char **split, \
			int (*pipe_fd)[2], int curr_index, int pipe_amm)
{
	char	**slice;
	char	**redir;

	reset_fds(1);
	redir = segment_full(split, curr_index);
	slice = segment_between_pipes(split, curr_index);
	set_pipe_fds(pipe_fd, pipe_amm, curr_index);
	has_to_redirect(central, redir);
	close_unused_pipes(pipe_fd, pipe_amm, curr_index);
	do_cmd(central, slice);
	ft_freesplit(slice);
	ft_freesplit(redir);
	reset_fds(1);
	exit(central->exit_val);
}

void	piper(t_central *central, char **split, int cmd_count)
{
	int		(*pipe_fd)[2];
	pid_t	pid;
	int		status;
	int		i;

	pipe_fd = malloc(sizeof(int [2]) * (cmd_count - 1));
	init_pipes(pipe_fd, cmd_count - 1);
	i = -1;
	while (++i < cmd_count)
	{
		pid = fork();
		if (pid == 0)
			execute_pipes(central, split, pipe_fd, i, cmd_count - 1);
		waitpid(pid, &status, 0);
	}
	close_all_pipes(pipe_fd, cmd_count - 1);
	central->exit_val = status;
	free(pipe_fd);
}
