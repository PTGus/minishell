/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:52:55 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/28 16:36:35 by gumendes         ###   ########.fr       */
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
int	should_revalue(t_envp **dupenv, char *exportion)
{
	char	**var;
	t_envp	*new;

	new = *dupenv;
	var = ft_split(exportion, '=');
	while (new)
	{
		if (ft_strcmp(new->var, var[0]) == 0)
		{
			if (ft_strchr(exportion, '='))
			{
				free(new->value);
				if (var[1])
					new->value = ft_strdup(var[1]);
				else
					new->value = ft_strdup("");
				new->has_equal = TRUE;
				new->visible_env = TRUE;
			}
			return (ft_freesplit(var), 1);
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

static void	do_exportions(t_central *central, t_input *cmd)
{
	t_envp	*new;
	t_input	*tmp;
	int		i;
	int		fail_flag;

	tmp = cmd;
	fail_flag = FALSE;
	while (tmp)
	{
		i = is_special_exportion(central, tmp->value);
		if (i == 2)
			fail_flag = TRUE;
		if (i == 0)
		{
			if (should_revalue(&central->dupenv, tmp->value) == 0)
			{
				new = new_env(tmp->value);
				insert_before_last(&central->dupenv, new);
			}
		}
		tmp = tmp->next;
	}
	central->exit_val = 0;
	if (fail_flag == TRUE)
		central->exit_val = 1;
}

/**
 * @brief Built-in function that behaves just like
 *  the export command.
 * @param split An array of arrays with the prompt received from read line.
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 */
void	ft_export(t_central *central, t_input *cmd)
{
	t_envp	*new;
	t_input	*tmp_cmd;

	new = central->dupenv;
	tmp_cmd = cmd;
	while (ft_strcmp(tmp_cmd->value, "export") != 0)
		tmp_cmd = tmp_cmd->next;
	if (!tmp_cmd->next)
	{
		declarex(&central->dupenv);
		central->exit_val = 0;
		return ;
	}
	do_exportions(central, tmp_cmd->next);
	reorder_dupenv(&central->dupenv);
}
