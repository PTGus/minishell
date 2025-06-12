/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:22:22 by david-fe          #+#    #+#             */
/*   Updated: 2025/05/23 17:22:39 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TO-DO : expansions into spaced text needs to be broken apart into nodes 
// 		: quote eraser

/**
 * @brief Returns quoted status of an element 
 * 0 = unquoted, 1 = inside '', 2 = inside ""
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

int	ft_quote_checker(t_input *node)
{
	//expand
	return (0);
}


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
			if (current && current->token == 0)
				ft_quote_checker(current);
			current = next;
		}
	}
	ft_print_list_array(central->cmd);
}
