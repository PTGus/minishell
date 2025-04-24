/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:00:05 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/24 14:01:27 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Built-in function that behaves just like
 *  the "unset" command.
 * @param dupenv The main list and head.
 * @param to_unset The variable to unset/delete.
 */
void	ft_unset(t_envp **dupenv, char *to_unset)
{
	t_envp	*tmp;

	if (!to_unset)
		return ;
	tmp = *dupenv;
	while (ft_strcmp(tmp->var, to_unset) != 0)
	{
		if (!tmp)
			return ;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	else
		env_delone(tmp);
}
