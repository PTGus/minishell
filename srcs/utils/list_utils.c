/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:29:49 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/09 15:42:37 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Adds a node to the end of the list, updates the head if necessary.
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 * @param The node to add to the end of the list.
 */
void	ft_lst_back(t_envp **dupenv, t_envp *curr)
{
	t_envp	*last;

	if (!*dupenv)
	{
		*dupenv = curr;
		return ;
	}
	last = lstlast(dupenv);
	last->next = curr;
	curr->prev = last;
}

/** @brief Gets last element of the list.
 *  @param lst  The list.
 * 	@return The last element of the list.
*/
t_envp	*lstlast(t_envp **dupenv)
{
	t_envp	*temp;

	temp = *dupenv;
	if (!temp)
		return (NULL);
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}
