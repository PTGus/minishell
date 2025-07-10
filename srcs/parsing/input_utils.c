/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:35:59 by david-fe          #+#    #+#             */
/*   Updated: 2025/07/10 15:08:19 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/** @brief Creates a new list node element
 *  @param content - content for the new element
 *  @return returns the new list
*/
t_input	*ft_input_new(void *value, int index)
{
	t_input	*new_node;

	new_node = malloc(sizeof(t_input));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->index = index;
	new_node->token = -1;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

/** @brief Gets last element of the list
 *  @param lst - list
 * 	@return Returns the last element of the list
*/
t_input	*ft_input_last(t_input *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

/** @brief Adds a new element to the end of the list
 *  @param lst - list
 * 	@param new - new element to add
*/
void	ft_input_add_back(t_input **lst, t_input *new_node) //LACKING PREV
{
	t_input	*last;

	last = ft_input_last(*lst);
	if (!last)
	{
		*lst = new_node;
		return ;
	}
	last->next = new_node;
	new_node->prev = last;
}

/** @brief Gets the number of elements in a list
 *  @param lst - list
 * 	@return Returns the number of elements in the list
*/
int	ft_input_size(t_input *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

/** @brief Applies a function to each element's content
 *  @param lst - list
 * 	@param f - function to apply
*/
void	ft_input_iter(t_input *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->value);
		lst = lst->next;
	}
}
