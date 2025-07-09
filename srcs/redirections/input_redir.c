/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:11:52 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/09 15:15:05 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_input(t_input *cmd)
{
	int		fd;
	t_input	*tmp;

	tmp = cmd->next;
	if (check_for_bad_redir(tmp->value) == 1)
		return (2);
	if (access(tmp->value, F_OK) == 0)
	{
		if (access(tmp->value, R_OK) == 0)
		{
			fd = open(tmp->value, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
			return (0);
		}
		else
			return (no_perms(tmp->value), 1);
	}
	else
		return (not_dir(tmp->value), 1);
}
