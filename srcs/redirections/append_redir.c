/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:10:23 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/28 14:08:51 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	append_redir(char *to_set)
{
	int	fd;

	if ((access(to_set, F_OK) != 0) || (access(to_set,  W_OK) != 0))
		return (no_perms(to_set), 2);
	else
	{
		fd = open(to_set, O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		return (0);
	}
}
