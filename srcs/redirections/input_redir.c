/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:11:52 by gumendes          #+#    #+#             */
/*   Updated: 2025/06/30 13:59:03 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_input(t_input *cmd)
{
	int		fd;
	t_input	*tmp;

	tmp = cmd->next;
	if (access(tmp->value, F_OK) == 0)
	{
		if (access(tmp->value, R_OK) == 0)
		{
			fd = open(tmp->value, O_RDONLY | O_APPEND);
			dup2(fd, STDIN_FILENO);
			close(fd);
			return (0);
		}
		else
		{
			no_perms(tmp->value);
			return (2);
		}
	}
	else
	{
		not_dir(tmp->value);
		return (2);
	}
}
