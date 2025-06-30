/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:57:49 by gumendes          #+#    #+#             */
/*   Updated: 2025/06/30 13:59:03 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_output(t_input *cmd)
{
	int		fd;
	t_input	*tmp;

	tmp = cmd->next;
	if (access(tmp->value, F_OK) == 0)
	{
		if (access(tmp->value, W_OK) != 0)
		{
			no_perms(tmp->value);
			return (1);
		}
		else
		{
			fd = open(tmp->value, O_TRUNC | O_WRONLY, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			return (0);
		}
	}
	else
	{
		fd = open(tmp->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		dup2(fd, STDOUT_FILENO);
		return (close(fd), 0);
	}
}
