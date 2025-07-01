/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:55:35 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/01 10:59:44 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_to_redirect(t_central *central, t_input *cmd)
{
	t_input *tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->token == REDIR_IN || tmp->token == REDIR_OUT
			|| tmp->token == APPEND_OUT || tmp->token == HERE_DOC
			|| tmp->token == HERE_DOC_Q)
			return (set_redirections(central, cmd));
		tmp = tmp->next;
	}
	return (1);
}

int	set_redirections(t_central *central, t_input *cmd)
{
	t_input *tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->token == REDIR_IN || tmp->token == REDIR_OUT
			|| tmp->token == APPEND_OUT || tmp->token == HERE_DOC
			|| tmp->token == HERE_DOC_Q)
		{
			if (do_redirection(tmp) == 2)
			{
				ft_putendl_fd("Invalid redirection", 2);
				central->exit_val = 1;
				return (2);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	do_redirection(t_input *cmd)
{
	if (cmd->token == REDIR_IN)
		return (set_input(cmd));
	else if (cmd->token == REDIR_OUT)
		return (set_output(cmd));
	else if (cmd->token == HERE_DOC || cmd->token == HERE_DOC_Q)
		return (ft_heredoc(cmd->next->value));
	else if (cmd->token == APPEND_OUT)
		return (append_redir(cmd));
	return (1);
}
