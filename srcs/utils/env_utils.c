/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:28:35 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/23 15:43:21 by gumendes         ###   ########.fr       */
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
			if (tmp->index == -1 && (!smallest || ft_strcmp(tmp->var, smallest->var) < 0))
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
