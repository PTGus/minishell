/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:11:52 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/27 16:15:59 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_input(char *to_set)
{
	int	fd;

	if (access(to_set, X_OK | R_OK) == 0)
	{
		fd = open(to_set, O_RDONLY, 0644);
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (0);
	}
	else
	{
		not_dir(to_set);
		return (1);
	}
}
