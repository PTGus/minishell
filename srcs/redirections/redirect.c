/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:55:35 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/10 16:51:22 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	allocate_heredoc_paths(t_central *central)
{
	int		i;
	t_input	*tmp;
	int		count;

	if (!central || !central->cmd)
		return (1);
	central->heredoc_paths = malloc(sizeof(char **) * central->matrix_len);
	if (!central->heredoc_paths)
		return (perror("malloc"), 1);
	i = -1;
	while (++i < central->matrix_len)
	{
		tmp = central->cmd[i];
		count = 0;
		while (tmp)
		{
			if (tmp->token == HERE_DOC || tmp->token == HERE_DOC_Q)
				count++;
			tmp = tmp->next;
		}
		central->heredoc_paths[i] = ft_calloc(count + 1, sizeof(char *));
		if (!central->heredoc_paths[i])
			return (perror("calloc"), 1);
	}
	return (0);
}

int	handle_all_heredocs(t_central *central)
{
	t_input	*tmp;
	int		i;

	i = 0;
	if (has_heredocs(central) == 0)
		return (0);
	allocate_heredoc_paths(central);
	while (i < central->matrix_len)
	{
		central->curr_cmd_idx = i;
		central->curr_heredoc_idx = 0;
		tmp = central->cmd[i];
		while (tmp)
		{
			if (tmp->token == HERE_DOC || tmp->token == HERE_DOC_Q)
			{
				if (ft_heredoc(central, tmp->next->value, tmp->token) == 130)
					return (130);
				central->curr_heredoc_idx++;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}

static int	do_redirection(t_central *central, t_input *cmd)
{
	char **path;

	if (cmd->token == REDIR_IN)
		return (set_input(cmd));
	else if (cmd->token == REDIR_OUT)
		return (set_output(cmd));
	else if (cmd->token == APPEND_OUT)
		return (append_redir(cmd));
	else if (cmd->token == HERE_DOC || cmd->token == HERE_DOC_Q)
	{
		path = &central->heredoc_paths[central->curr_cmd_idx][central->curr_heredoc_idx];
		if (!*path)
		{
			ft_putstr_fd("minishell: heredoc path is missing\n", STDERR_FILENO);
			return (1);
		}
		return (redirect_doc_path(path));
		central->curr_heredoc_idx++;
	}
	return (1);
}

static int	set_redirections(t_central *central, t_input *cmd)
{
	t_input *tmp;
	int		i;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->token == REDIR_IN || tmp->token == REDIR_OUT
			|| tmp->token == APPEND_OUT
			|| tmp->token == HERE_DOC || tmp->token == HERE_DOC_Q)
		{
			i = do_redirection(central, tmp);
			if (i != 0)
				return (central->exit_val = i, i);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	has_to_redirect(t_central *central, t_input *cmd)
{
	t_input *tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->token == REDIR_IN || tmp->token == REDIR_OUT
			|| tmp->token == APPEND_OUT
			|| tmp->token == HERE_DOC || tmp->token == HERE_DOC_Q)
			return (set_redirections(central, cmd));
		tmp = tmp->next;
	}
	return (0);
}
