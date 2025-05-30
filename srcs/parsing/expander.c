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

int ft_get_expand_end(char *str, int j) //TO_DO -> continue first flag logic
{
	int first_flag;
	int quote_flag;

	first_flag = 0;
	quote_flag = 0;
	while (str[j])
	{
		if (str[j] == '\"' && quote_flag == 0 )
			quote_flag = 1;
		else if (str[j] == '?' && quote_flag == 0)
			return (-1);
		else if (str[j] == '$' && quote_flag == 0)
			return (-2);
		else if ((str[j] >= 'a' && str[j] <= 'z') || (str[j] >= 'A' && str[j] <= 'Z')
			|| (str[j] >= '0' && str[j] <= '9') || str[j] == '_')
			j++;
	}
	return (j);
}

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
			ft_get_expand_end(node->value, i + 1);
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
