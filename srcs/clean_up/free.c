/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:55:17 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/31 12:41:48 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_doc(char *line)
{
	if (!line)
		return ;
	free(line);
}

/**
 * @brief Calls all the clean up functions to free all the allocated memory.
 * @param central A struct that contains pointers to
 *  all the neccessary variables and lists.
 */
void	clean_all(t_central *central)
{
	free_heredoc_paths(central);
	free_central_cmd(central);
	free_env(&central->dupenv);
	free(central);
	rl_clear_history();
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
	to_free->var = NULL;
	free(to_free->value);
	to_free->value = NULL;
	free(to_free);
}

/**
 * @brief Cleans all the memory utilized by
 *  dupenv linked list by freeing it node by node.
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 */
void	free_env(t_envp **dupenv)
{
	t_envp	*tmp;

	if (!dupenv)
		return ;
	while (*dupenv)
	{
		tmp = (*dupenv)->next;
		ft_envfreeone(*dupenv);
		(*dupenv) = tmp;
	}
	free(*dupenv);
}
