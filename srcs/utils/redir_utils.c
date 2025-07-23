/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:25:10 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/23 17:04:40 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_bad_redir(t_input *cmd)
{
	if (!cmd)
		return (no_redir_err(), 1);
	if (ft_strcmp(cmd->value, ">") == 0 || ft_strcmp(cmd->value, "<") == 0
		|| ft_strcmp(cmd->value, ">>") == 0 || ft_strcmp(cmd->value, "<<") == 0)
		return (bad_redir_token(cmd->value), 2);
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

int	has_heredocs(t_central *central)
{
	int		i;
	t_input	*tmp;

	if (!central || !central->cmd)
		return (0);
	i = 0;
	while (i < central->matrix_len)
	{
		tmp = central->cmd[i];
		while (tmp)
		{
			if (tmp->token == HERE_DOC || tmp->token == HERE_DOC_Q)
				return (1);
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}
