/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:05:25 by gumendes          #+#    #+#             */
/*   Updated: 2025/06/25 11:09:53 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_special_exportion(t_central *central, char **split)
{
	int	i;

	i = 0;
	while (split[1][i])
	{
		if (split[1][i] == '=')
			break ;
		i++;
	}
	if (split[1][i] == '=' && split[1][i + 1] == '\0')
		return (hidden_export(central, split, TRUE), 1);
	else if (split[1][i] != '=')
		return (hidden_export(central, split, FALSE), 1);
	return (0);
}

void	print_declaration(t_envp *curr)
{
	if (curr->has_equal == FALSE)
		printf("declare -x %s\n", curr->var);
	else if (curr->has_equal == TRUE && curr->value == NULL)
		printf("declare -x %s=\"\"\n", curr->var);
	else
		printf("declare -x %s=\"%s\"\n", curr->var, curr->value);
}

void	hidden_export(t_central *central, char **split, int has_equal)
{
	t_envp	*new;

	if (should_revalue(&central->dupenv, split) == 0)
	{
		new = new_valuesless_env(split[1]);
		new->visible_env = FALSE;
		new->has_equal = has_equal;
		insert_before_last(&central->dupenv, new);
	}
}

/**
 * @brief Creates a new node with the given value.
 * @param nbr The value that this new node will assume.
 * @return The new node.
 */
t_envp	*new_valuesless_env(char *envp)
{
	t_envp	*new;
	int		i;

	new = ft_calloc(1, sizeof(t_envp));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	if (envp[0] == '_')
		new->index = -2;
	else
		new->index = -1;
	i = 0;
	while (envp[i])
	{
		if (envp[i] == '=')
			break ;
		i++;
	}
	if (envp[i] == '=')
		new->var = ft_substr(envp, 0, i);
	else
		new->var = ft_strdup(envp);
	new->value = NULL;
	return (new);
}
