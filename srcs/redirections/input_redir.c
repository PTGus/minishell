/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:11:52 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/29 13:29:33 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_input(char *to_set)
{
	int	fd;

	if (access(to_set, F_OK) == 0)
	{
		if (access(to_set, R_OK) == 0)
		{
			fd = open(to_set, O_RDONLY | O_APPEND);
			dup2(fd, STDIN_FILENO);
			close(fd);
			return (0);
		}
		else
		{
			no_perms(to_set);
			return (2);
		}
	}
	else
	{
		not_dir(to_set);
		return (2);
	}
}
