/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:57:49 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/15 13:20:41 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_output(char **split)
{
	int	i;
	int	fd;

	i = -1;
	while (split[++i])
	{
		if (ft_strcmp(split[i], ">") == 0)
		{
			i++;
			fd = open(split[i], O_CREAT | O_TRUNC | O_RDWR, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (ft_strcmp(split[i], ">>") == 0)
		{
			i++;
			if (access(split[i], F_OK) != 0)
				fd = open(split[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				fd = open(split[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	}
}

void	redirect_output(t_central *central, char **split)
{
	int	i;

	i = 0;
	(void)central;
	while (split[i])
	{
		if (split[i][0] == '>')
		{
			set_output(split + i);
			i++;
		}
		i++;
	}
}
