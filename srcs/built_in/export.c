/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:52:55 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/23 15:43:32 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Adds a node to the to a position before the end of the list, updates the head if necessary.
 */
void	insert_before_last(t_envp **dupenv, t_envp *curr)
{
	t_envp *last;
	t_envp *b_last;

	if (!*dupenv)
	{
		*dupenv = curr;
		return;
	}
	last = lstlast(*dupenv);
	b_last = last->prev;
	b_last->next = curr;
	curr->prev = b_last;
	curr->next = last;
	last->prev = curr;
}

int	should_revalue(t_envp **dupenv, char**split)
{
	char	**var;
	t_envp	*new;

	new = *dupenv;
	var = ft_split(split[1], '=');
	while (new)
	{
		if (ft_strcmp(new->var, var[0]) == 0)
		{
			new->value = NULL;
			new->value = ft_strdup(var[1]);
			ft_free_split(var);
			return (1);
		}
		new = new->next;
	}
	ft_free_split(var);
	return (0);
}

void	declarex(t_envp **dupenv)
{
	t_envp	*tmp;
	int		i;

	i = 0;
	while (1)
	{
		tmp = *dupenv;
		while (tmp)
		{
			if (tmp->index == i)
			{
				printf("declare -x %s=\"%s\"\n", tmp->var, tmp->value);
				break ;
			}
			tmp = tmp->next;
		}
		if (!tmp)
			break ;
		i++;
	}
}

void	ft_export(char **split, t_envp **dupenv)
{
	t_envp	*new;
	int		i;

	new = *dupenv;
	i = 0;
	if (!split[1])
	{
		declarex(dupenv);
		return ;
	}
	while (split[1][i])
	{
		if (split[1][i] == '=')
			break ;
		i++;
	}
	if (split[1][i] != '=')
		return ;
	if (should_revalue(dupenv, split) == 0)
	{
		new = new_env(split[1]);
		insert_before_last(dupenv, new);
	}
	reorder_dupenv(dupenv);
}
