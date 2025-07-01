/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:57:49 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/01 10:50:32 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_output(t_input *cmd)
{
	int		fd;
	t_input	*tmp;

	tmp = cmd->next;
	if (!tmp || ft_strcmp(tmp->value, "") == 0)
		return (2);
	if (access(tmp->value, F_OK) == 0)
	{
		if (access(tmp->value, W_OK) != 0)
			return (no_perms(tmp->value), 1);
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
