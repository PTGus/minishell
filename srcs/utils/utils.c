/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:04:40 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/28 13:01:33 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_redir(t_input *cmd)
{
	if (cmd->token == REDIR_IN)
		return (1);
	if (cmd->token == REDIR_OUT)
		return (2);
	if (cmd->token == APPEND_OUT)
		return (3);
	if (cmd->token == HERE_DOC || cmd->token == HERE_DOC_Q)
		return (4);
	return (0);
}

t_input	*find_cmd(t_input *cmd)
{
	t_input	*tmp;
	int		tmp_check;

	tmp = cmd;
	while (tmp && tmp->token != ARGUMENT)
	{
		tmp_check = is_redir(tmp);
		if (tmp_check != 0 && tmp->next->next != NULL)
			tmp = tmp->next->next;
		else if (tmp_check != 0 && tmp->next->next == NULL)
			tmp = NULL;
		else if (tmp->token == DELETE && tmp->next != NULL)
			tmp = tmp->next;
		else if (tmp->token == DELETE && tmp->next == NULL)
			return (tmp);
	}
	return (tmp);
}

void	has_shell_operator(t_central *central, char *rl)
{
	if (to_pipe(central) == 1)
	{
		if (handle_all_heredocs(central) == 2)
			return ;
		central->curr_cmd_idx = 0;
		central->curr_hdc_idx = 0;
		if (has_to_redirect(central, central->cmd[0]) != 0)
		{
			post_loop_cleanup(central, rl);
			return ;
		}
		do_solo(central, central->cmd[0]);
		free_heredoc_paths(central);
	}
	post_loop_cleanup(central, rl);
}

/**
 * @brief Compares 2 strings to check whether they are the same or not.
 * @return Returns 0 when the strings are equal, < 0 when the s1
 *  is of lower ascii value and > 0 when s1 is of higher ascii value.
 */
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void	increase_shlvl(t_envp **dupenv)
{
	t_envp	*tmp;
	int		tmp_val;

	tmp = ft_getenv(dupenv, "SHLVL");
	if (!tmp)
	{
		tmp = new_env("SHLVL=0");
		insert_before_last(dupenv, tmp);
		reorder_dupenv(dupenv);
		return ;
	}
	tmp_val = ft_atoi(tmp->value);
	tmp_val++;
	free(tmp->value);
	tmp->value = NULL;
	tmp->value = ft_itoa(tmp_val);
}
