/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:22:22 by david-fe          #+#    #+#             */
/*   Updated: 2025/06/30 16:32:47 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Returns quoted status of an element
 *  0 = unquoted, 1 = inside '', 2 = inside ""
 * @param prompt Full input from readline
 * @param end_pos Last element to be checked
 * if end_pos -1 examines whole string
 */
int	ft_is_quoted(char *prompt, int end_pos)
{
	int	i;
	int	quote_flag;

	i = -1;
	quote_flag = 0;
	if (end_pos == -1)
		end_pos = ft_strlen(prompt) - 1;
	while (prompt[++i] && i <= end_pos)
	{
		if (prompt[i] == '\'' && quote_flag == 0)
			quote_flag = 1;
		else if (prompt[i] == '\'' && quote_flag == 1)
			quote_flag = 0;
		else if (prompt[i] == '\"' && quote_flag == 0)
			quote_flag = 2;
		else if (prompt[i] == '\"' && quote_flag == 2)
			quote_flag = 0;
	}
	return (quote_flag);
}

/**
 * @brief	Iterates through the command nodes of ARG type
 *  and call quote check to erase unquoted quotes.
 */
void	ft_quote_eraser(t_central *central)
{
	int		i;
	t_input	*current;
	t_input	*next;

	i = -1;
	while (central->cmd[++i])
	{
		current = central->cmd[i];
		while (current)
		{
			next = current->next;
			if (current->value && current->token == 0)
				if (ft_quote_checker(current) == 1)
					ft_free_list_err(central, NULL, NULL);
			current = next;
		}
	}
}

/**
 * @brief	Iterates throught the node value and counts unquoted quotes
 * to erase, if >0 calls to erase
 * @return	0 if correct, 1 on malloc error from erase_node_quotes
 */
int	ft_quote_checker(t_input *node)
{
	int	j;
	int	count;

	count = 0;
	j = -1;
	while (node->value[++j])
	{
		if ((node->value[j] == '\"' && ft_is_quoted(node->value, j) != 1)
			|| (node->value[j] == '\'' && ft_is_quoted(node->value, j) != 2))
			count++;
	}
	if (count > 0)
		return (ft_erase_node_quotes(node, count));
	return (0);
}

/**
 * @brief	Alloc's and assigns new value to node with len - count of
 * unquoted quotes
 * @param	new_val - new node value with unquoted quotes erased
 * @param	new_len - length of new val without the quotes to erase
 * @return	0 if correct, 1 on malloc error
 */
int	ft_erase_node_quotes(t_input *node, int count)
{
	int		i;
	int		j;
	int		new_len;
	char	*new_val;
	char	*temp;

	i = 0;
	j = 0;
	new_len = ft_strlen(node->value) - count;
	new_val = ft_calloc((new_len + 1), sizeof(char));
	if (!new_val)
		return (1);
	while (i < new_len)
	{
		if ((node->value[j] == '\"' && ft_is_quoted(node->value, j) != 1)
			|| (node->value[j] == '\'' && ft_is_quoted(node->value, j) != 2))
			j++;
		else
			new_val[i++] = node->value[j++];
	}
	temp = node->value;
	node->value = new_val;
	free(temp);
	return (0);
}
