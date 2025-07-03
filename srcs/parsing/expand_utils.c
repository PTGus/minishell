/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:10:46 by david-fe          #+#    #+#             */
/*   Updated: 2025/07/03 10:57:56 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief	Checks if str at i pos is $, has a value after
 * and is not inside '', and not immediately followed by a "
 * @return	0 if correct, 1 on malloc error
*/
int	ft_str_expand(t_central *central, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] == '$' && str[i + 1]
			&& ft_is_quoted(str, i) != 1
			&& (str[i + 1] != '\"'))
		{
			j = ft_get_expand_end(str, i + 1);
			if (ft_execute_expand(central, &str, i, j) == 1)
				return (1);
			i = 0;
		}
		else
			i++;
	}
	return (0);
}

/**
 * @brief	Gets value of expand from dupenv, with PID for $ (no getpid),
 * and ? for exit value from most recent pipe
*/
char	*ft_get_dupenv_val(t_central *central, char *str)
{
	t_envp	*tmp;

	tmp = central->dupenv;
	if (ft_strncmp(str, "$", 1) == 0)
		return (ft_strdup("PID"));
	else if (ft_strncmp(str, "?", 1) == 0)
		return (ft_itoa(central->exit_val));
	else
	{
		tmp = ft_getenv(&central->dupenv, str);
		if (!tmp)
			return (NULL);
		return (ft_strdup(tmp->value));
	}
}

/**
 * @brief	Checks for unquoted spaces and if found, assigns a new value for
 * the current node and creates a new one of the rest
 * @param	old_val - Buffer for entire old value of current node
 * @param	split_node - New node to hold the rest of the value of old node
*/
int	ft_is_node_spaced(t_input *node)
{
	int		i;
	char	*old_val;
	t_input	*split_node;
	int		len;

	i = -1;
	while (node->value[++i])
	{
		if (node->value[i] == ' ' && ft_is_quoted(node->value, i) == 0)
		{
			old_val = node->value;
			node->value = ft_substr(old_val, 0, i);
			len = ft_strlen(old_val + i + 1);
			if (old_val[i + 1])
			{
				split_node = ft_input_new(
						ft_substr(old_val, i + 1, len), node->index + 1);
				ft_insert_split_node(node, split_node);
				free(old_val);
			}
		}
	}
	return (0);
}

/**
 *	@brief	Inserts new node into the list and increments all indexes after
 *	@param	first - node with the first part of old val
 *	@param	second - node with the remainder of old val
*/
void	ft_insert_split_node(t_input *first, t_input *second)
{
	t_input	*next;
	t_input	*current;

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
