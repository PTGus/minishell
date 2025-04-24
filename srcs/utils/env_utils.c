/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:28:35 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/24 17:20:14 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	organise_env(t_envp **dupenv)
{
	t_envp	*tmp;
	t_envp	*smallest;
	int		i;

	i = 0;
	while (1)
	{
		tmp = *dupenv;
		smallest = NULL;
		while (tmp)
		{
			if (tmp->index == -1 && \
				(!smallest || ft_strcmp(tmp->var, smallest->var) < 0))
				smallest = tmp;
			tmp = tmp->next;
		}
		if (!smallest)
			break ;
		smallest->index = i;
		i++;
	}
}

void	reorder_dupenv(t_envp **dupenv)
{
	t_envp	*tmp;

	tmp = *dupenv;
	while (tmp)
	{
		if (tmp->index >= 0)
			tmp->index = -1;
		tmp = tmp->next;
	}
	organise_env(dupenv);
}

void	env_delone(t_envp *to_del)
{
	t_envp	*tmp1;
	t_envp	*tmp2;

	if (to_del->prev != NULL && to_del->next != NULL)
	{
		tmp1 = to_del->prev;
		tmp2 = to_del->next;
		tmp1->next = tmp2;
		tmp2->prev = tmp1;
		ft_envfreeone(to_del);
	}
	else if (to_del->prev != NULL && to_del->next == NULL)
	{
		tmp1 = to_del->prev;
		tmp1->next = NULL;
		ft_envfreeone(to_del);
	}
	else if (to_del->prev == NULL && to_del->next != NULL)
	{
		tmp2 = to_del->next;
		tmp2->prev = NULL;
		ft_envfreeone(to_del);
	}
}
