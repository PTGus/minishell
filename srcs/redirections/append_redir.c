/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:10:23 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/03 11:01:59 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	append_redir(t_input *cmd)
{
	int		fd;
	t_input	*tmp;

	tmp = cmd->next;
	if (check_for_bad_redir(tmp->value) == 1)
		return (2);
	if ((access(tmp->value, F_OK) == 0) && (access(tmp->value, W_OK) != 0))
		return (no_perms(tmp->value), 1);
	else
	{
		fd = open(tmp->value, O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		return (0);
	}
}
