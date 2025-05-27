/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:25:10 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/12 15:39:12 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_fds(int status)
{
	static int	org_stdin;
	static int	org_stdout;

	if (status == 0)
	{
		org_stdin = -1;
		org_stdout = -1;
		org_stdin = dup(STDIN_FILENO);
		org_stdout = dup(STDOUT_FILENO);
	}
	else if (status == 1)
	{
		dup2(org_stdin, STDIN_FILENO);
		dup2(org_stdout, STDOUT_FILENO);
	}
	else if (status == 2)
	{
		close(org_stdin);
		close(org_stdout);
	}
}
