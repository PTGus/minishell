/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:01:44 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/19 14:31:27 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**separate_split(char **split, int i)
{
	char	**new;
	int		j;

	j = i;
	while(split[j])
		j++;
	new = ft_calloc(sizeof(char *), j - i + 1);
	j = 0;
	while (split[i])
	{
		new[j] = ft_strdup(split[i]);
		i++;
		j++;
	}
	new[j] = NULL;
	return (new);
}

void	piper(t_central *central, char **split, int pl)
{
	char	**pipe_split;
	int		pipe_fd[2];
	pid_t	pid;

	pipe_split = separate_split(split, pl + 1);
	while (split[pl])
	{
		free(split[pl]);
		split[pl] = NULL;
		pl++;

	}
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0) // Child: executes left side of pipe
	{
		dup2(pipe_fd[1], STDOUT_FILENO); // stdout → pipe write
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		commander(central, split);
		exit(1); // exit if exec fails
	}
	else // Parent: executes right side of pipe
	{
		dup2(pipe_fd[0], STDIN_FILENO); // stdin ← pipe read
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		commander(central, pipe_split);
	}
}
