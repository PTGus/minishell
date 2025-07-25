/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:25:10 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/03 15:01:53 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_bad_redir(char *to_redir)
{
	if (ft_strcmp(to_redir, ">") == 0 || ft_strcmp(to_redir, "<") == 0
		|| ft_strcmp(to_redir, ">>") == 0 || ft_strcmp(to_redir, "<<") == 0)
		return (bad_redir_token(to_redir), 1);
	return (0);
}

void	reset_fds(int status)
{
	static int	org_stdin;
	static int	org_stdout;
	static int	org_stderr;

	if (status == 0)
	{
		org_stdin = -1;
		org_stdout = -1;
		org_stderr = -1;
		org_stdin = dup(STDIN_FILENO);
		org_stdout = dup(STDOUT_FILENO);
		org_stderr = dup(STDERR_FILENO);
	}
	else if (status == 1)
	{
		dup2(org_stdin, STDIN_FILENO);
		dup2(org_stdout, STDOUT_FILENO);
		dup2(org_stderr, STDERR_FILENO);
	}
	else if (status == 2)
	{
		close(org_stdin);
		close(org_stdout);
		close(org_stderr);
	}
}
