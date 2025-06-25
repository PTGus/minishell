/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:52:55 by gumendes          #+#    #+#             */
/*   Updated: 2025/06/25 11:00:09 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Checks whether an env already exists, if so revalues
 *  it, if not tells the calling function to create it.
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 * @param split An array of arrays with the prompt received from read line.
 * @return Returns 0 when the specified variable doesn't exist
 *  and should be created,
 * and 1 when the variable already exists and was revalued.
 */
int	should_revalue(t_envp **dupenv, char**split)
{
	char	**var;
	t_envp	*new;

	new = *dupenv;
	var = ft_split(split[1], '=');
	while (new)
	{
		if ((ft_strcmp(new->var, var[0]) == 0)/*  && (new->has_equal == TRUE) */)
		{
			free(new->value);
			new->value = NULL;
			if (var[1] == NULL)
				return (1);
			new->value = ft_strdup(var[1]);
			ft_freesplit(var);
			return (1);
		}
		new = new->next;
	}
	ft_freesplit(var);
	return (0);
}

/**
 * @brief Mimics the behaviour of the export function without
 *  any additional paramters.
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 */
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
				print_declaration(tmp);
				break ;
			}
			tmp = tmp->next;
		}
		if (!tmp)
			break ;
		i++;
	}
}

/**
 * @brief Built-in function that behaves just like
 *  the export command.
 * @param split An array of arrays with the prompt received from read line.
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 */
void	ft_export(t_central *central, char **split)
{
	t_envp	*new;
	int		i;

	new = central->dupenv;
	i = -1;
	if (!split[1])
	{
		declarex(&central->dupenv);
		central->exit_val = 0;
		return ;
	}
	if (is_special_exportion(central, split) == 0)
	{
		if (should_revalue(&central->dupenv, split) == 0)
		{
			new = new_env(split[1]);
			insert_before_last(&central->dupenv, new);
		}
	}
	reorder_dupenv(&central->dupenv);
	central->exit_val = 0;
}
