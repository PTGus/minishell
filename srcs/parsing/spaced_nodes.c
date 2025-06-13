/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaced_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:10:46 by david-fe          #+#    #+#             */
/*   Updated: 2025/06/13 16:11:09 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_insert_split_node(t_input *first, t_input *second)
{
	t_input *next;
	t_input *current;

	second->token = 0;
	next = first->next;
	first->next = second;
	second->prev = first;
	second->next = next;
	current = next;
	while (current)
	{
		next = current->next;			
		current->index += 1;
		current = next;
	}
}

void	ft_is_node_spaced(t_input *node)
{
	int	i;
	char *old_val;
	t_input *split_node;

	old_val = NULL;
	i = -1;
	while (node->value[++i])
	{
		if (node->value[i] == ' ' && ft_is_quoted(node->value, i) == 0)
		{
			old_val = node->value;
			node->value = ft_substr(old_val, 0, i);
			if (old_val[i + 1])
			{
				split_node = ft_input_new(ft_substr(old_val, i + 1,
						ft_strlen(old_val + i + 1)), node->index + 1);
				ft_insert_split_node(node, split_node);
				free(old_val);
			}
		}
	}
}
