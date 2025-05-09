/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:55:17 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/09 10:36:57 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_all(t_central *central)
{
	free_env(&central->dupenv);
	free(central);
}

/**
 * @brief Frees all the memory allocated to an array of arrays.
 * @param split The array to free.
 */
void	ft_freesplit(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/**
 * @brief Cleans all the memory utilized by
 *  dupenv linked list's node by freeing all the variables memory within it.
 * @param to_free The node of the dupenv list to free.
 */
void	ft_envfreeone(t_envp *to_free)
{
	if (!to_free)
		return ;
	free(to_free->var);
	free(to_free->value);
	free(to_free);
}

/**
 * @brief Cleans all the memory utilized by
 *  dupenv linked list by freeing it node by node.
 * @param dupenv The main list and head.
 */
void	free_env(t_envp **dupenv)
{
	t_envp	*tmp;

	if (!dupenv || !*dupenv)
		return ;
	while (*dupenv)
	{
		tmp = (*dupenv)->next;
		ft_envfreeone(*dupenv);
		*dupenv = tmp;
	}
	*dupenv = NULL;
}
