/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:28:35 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/28 15:59:37 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Sets a index for all the members of dupenv in ascending ascii order.
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 */
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
			if (tmp->index == -1
				&& (!smallest || ft_strcmp(tmp->var, smallest->var) < 0))
				smallest = tmp;
			tmp = tmp->next;
		}
		if (!smallest)
			break ;
		smallest->index = i;
		i++;
	}
}

/**
 * @brief Reorders the index of the members of the dupenv
 *  linked list whenever one is deleted or a new one is created.
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 */
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

/**
 * @brief Deletes a node of the dupenv linked list and sets the
 *  pointers of the previous and next nodes to point to the correct nodes.
 * @param to_del The node of the dupenv linked list to delete.
 */
void	env_delone(t_envp *to_del)
{
	t_envp	*tmp1;
	t_envp	*tmp2;

	if (!to_del)
		return ;
	if (to_del->prev && to_del->next)
	{
		tmp1 = to_del->prev;
		tmp2 = to_del->next;
		tmp1->next = tmp2;
		tmp2->prev = tmp1;
	}
	else if (to_del->prev)
		to_del->prev->next = NULL;
	else if (to_del->next)
		to_del->next->prev = NULL;
	ft_envfreeone(to_del);
}

/**
 * @brief Adds a node to the to a position before
 *  the end of the list, updates the head if necessary.
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 * @param curr The node to be inserted.
 */
void	insert_before_last(t_envp **dupenv, t_envp *curr)
{
	t_envp	*last;
	t_envp	*b_last;

	if (!*dupenv)
	{
		*dupenv = curr;
		return ;
	}
	last = lstlast(dupenv);
	b_last = last->prev;
	if (!b_last)
	{
		curr->next = last;
		curr->prev = NULL;
		last->prev = curr;
		*dupenv = curr;
		return ;
	}
	b_last->next = curr;
	curr->prev = b_last;
	curr->next = last;
	last->prev = curr;
}


t_envp	*ft_getenv(t_envp **dupenv, char *to_find)
{
	t_envp	*tmp;

	tmp = *dupenv;
	while (tmp && (ft_strcmp(tmp->var, to_find) != 0))
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	return (tmp);
}
