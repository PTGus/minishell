/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:00:05 by gumendes          #+#    #+#             */
/*   Updated: 2025/06/16 16:48:19 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Built-in function that behaves just like
 *  the "unset" command.
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 * @param to_unset The variable to unset/delete.
 */
void	ft_unset(t_central *central, char *to_unset)
{
	t_envp	*tmp;

	if (!to_unset)
	{
		central->exit_val = 0;
		return ;
	}
	tmp = central->dupenv;
	while (tmp != NULL && ft_strcmp(tmp->var, to_unset) != 0)
		tmp = tmp->next;
	if (!tmp)
	{
		central->exit_val = 0;
		return ;
	}
	else
	{
		central->exit_val = 0;
		env_delone(tmp);
		reorder_dupenv(&central->dupenv);
	}
}
