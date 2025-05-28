/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:12:17 by david-fe          #+#    #+#             */
/*   Updated: 2025/05/26 15:18:27 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
int ft_get_expand_end(char *str, int i, int quote_type)
{
	int j;

	j = 0;
	while (str[i + j])
	{
		if (quote_type == UNQUOTED)
		{

		}
		else if (quote_type == DOUBLE_Q)
		{

		}
		j++;
	}
}
*/
//iter through list
//if a $ is found unquoted use getenv to substitute
//remeber double quotes vs single
void ft_check_expand(t_input *node)
{
	int i;

	i = -1;
	while (node->value[++i])
	{
		if (node->value[i] == '$' && node->value[i + 1]
			&& ft_is_quoted(node->value, i) != 1)
		{
			printf("expander at %i!\n", i);
			/*
			if (ft_is_quoted(node->value[i + 1]) == UNQUOTED) 
				ft_get_expand_end(node->value, i + 1, 0);
			else if (ft_is_quoted(node->value[i + 1]) == DOUBLE_Q)
				ft_get_expand_end(node->value, i + 1, 2);
			*/
		}
	}
}

int	ft_expander(t_central *central)
{
	int		i;
	t_input *current;
	t_input *next;

	i = -1;
	while (central->cmd[++i])
	{
		current = central->cmd[i];
		while (current)
		{
			next = current->next;
			if (next->token == 0)
				ft_check_expand(next);
			current = next;
		}

	}
	return (0);
}
