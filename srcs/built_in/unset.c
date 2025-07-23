/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:00:05 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/23 13:27:18 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	unseter(t_central *central, t_input *cmd)
{
	t_envp	*tmp;

	while (cmd && cmd->token == ARGUMENT)
	{
		tmp = ft_getenv(&central->dupenv, cmd->value);
		if (tmp)
		{
			if (tmp == central->dupenv)
				central->dupenv = tmp->next;
			env_delone(tmp);
		}
		cmd = cmd->next;
	}
}

/**
 * @brief Built-in function that behaves just like
 *  the "unset" command.
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 * @param to_unset The variable to unset/delete.
 */
void	ft_unset(t_central *central, t_input *cmd)
{
	t_envp	*tmp_env;

	if (!cmd)
		return (central->exit_val = 0, (void) 0);
	tmp_env = central->dupenv;
	while (tmp_env != NULL && ft_strcmp(tmp_env->var, cmd->value) != 0)
		tmp_env = tmp_env->next;
	if (!tmp_env)
	{
		central->exit_val = 0;
		return ;
	}
	else
	{
		unseter(central, cmd);
		reorder_dupenv(&central->dupenv);
		central->exit_val = 0;
	}
}
