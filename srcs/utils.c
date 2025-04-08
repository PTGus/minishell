/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:04:40 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/07 16:21:00 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_split(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*pather(char *cmd)
{
	int		i;
	char	*exec;
	char	**all_paths;
	char	*path_part;
	char	**split_cmds;

	all_paths = ft_split(getenv("PATH"), ':');
	split_cmds = ft_split(cmd, ' ');
	i = -1;
	while (all_paths[++i])
	{
		path_part = ft_strjoin(all_paths[i], "/");
		exec = ft_strjoin(path_part, split_cmds[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_split(split_cmds);
			ft_free_split(all_paths);
			return (exec);
		}
		free(exec);
	}
	ft_free_split(split_cmds);
	ft_free_split(all_paths);
	return (cmd);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
