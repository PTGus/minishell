/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:01:44 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/21 17:12:48 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**separate_split(char **split)
{
	static int	start;
	char		**new;
	int			i;
	int			j;

	if (!split || !split[start])
		return (NULL);
	i = start;
	while (split[i] && split[i][0] != '|')
		i++;
	new = ft_calloc(sizeof(char *), i - start + 1);
	if (!new)
		return (NULL);
	j = 0;
	while (start < i)
	{
		new[j] = ft_strdup(split[start]);
		start++;
		j++;
	}
	new[j] = NULL;
	if (split[start] && split[start][0] == '|')
		start++;
	return (new);
}

void	execute_pipes(t_central *central, char **split, int pipe_fd[][2], int curr_index, int pipe_amm)
{
	char	**new_split;

	close_unused_pipes(pipe_fd, pipe_amm, curr_index);
	set_pipe_fds(pipe_fd, pipe_amm, curr_index);
	do_cmd(separate_split(split), central);
}

void	piper(t_central *central, char **split, int pipe_amm)
{
	int		i;
	int		pipe_fd[pipe_amm][2];
	int		status;
	pid_t	pid;

	i = 0;
	status = 0;
	init_pipes(pipe_fd, pipe_amm);
	while (i < pipe_amm)
	{
		pid = fork();
		if (pid == 0)
			execute_pipes(central, split, pipe_fd, i, pipe_amm);
		else if (pid < 0)
		{
			perror("fork");
			return;
		}
		i++;
	}
}
