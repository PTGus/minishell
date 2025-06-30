/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:57:49 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/29 13:34:08 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_output(char *to_set)
{
	int	fd;

	if (access(to_set, F_OK) == 0)
	{
		if (access(to_set, W_OK) != 0)
		{
			no_perms(to_set);
			return (1);
		}
		else
		{
			fd = open(to_set, O_TRUNC | O_WRONLY, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			return (0);
		}
	}
	else
	{
		fd = open(to_set, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		return (0);
	}
}
