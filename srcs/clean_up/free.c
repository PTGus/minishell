/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:55:17 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/03 11:11:57 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_doc(char *rl_doc, char *tmp)
{
	if (tmp && tmp != rl_doc)
		free(tmp);
	if (!rl_doc)
		return ;
	free(rl_doc);
}

/**
 * @brief Calls all the clean up functions to free all the allocated memory.
 * @param central A struct that contains pointers to
 *  all the neccessary variables and lists.
 */
void	clean_all(t_central *central)
{
	free_env(central->dupenv);
	free_central_cmd(central);
	free(central);
}

/**
 * @brief Frees all the memory allocated to an array of arrays.
 * @param split The array of arrays to free.
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
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 */
void	free_env(t_envp *dupenv)
{
	t_envp	*tmp;

	if (!dupenv)
		return ;
	while (dupenv)
	{
		tmp = dupenv->next;
		ft_envfreeone(dupenv);
		dupenv = tmp;
	}
}
