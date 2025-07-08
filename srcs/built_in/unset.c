/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:00:05 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/08 10:18:16 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Built-in function that behaves just like
 *  the "unset" command.
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 * @param to_unset The variable to unset/delete.
 */
void	ft_unset(t_central *central, t_input *cmd)
{
	t_envp	*tmp_env;
	t_input	*tmp_cmd;

	if (!cmd)
	{
		central->exit_val = 0;
		return ;
	}
	tmp_env = central->dupenv;
	tmp_cmd = cmd;
	while (tmp_env != NULL && ft_strcmp(tmp_env->var, tmp_cmd->value) != 0)
		tmp_env = tmp_env->next;
	if (!tmp_env)
	{
		central->exit_val = 0;
		return ;
	}
	else
	{
		central->exit_val = 0;
		env_delone(tmp_env);
		reorder_dupenv(&central->dupenv);
	}
}
