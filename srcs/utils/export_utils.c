/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:05:25 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/22 17:18:38 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_declaration(t_envp *curr)
{
	if (curr->value == NULL)
		printf("declare -x %s\n", curr->var);
	else
		printf("declare -x %s=\"%s\"\n", curr->var, curr->value);
}

void	hidden_export(t_central *central, char **split)
{
	t_envp	*new;

	if (should_revalue(&central->dupenv, split) == 0)
	{
		new = new_env(split[1]);
		new->visible_env = FALSE;
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

	new = ft_calloc(1, sizeof(t_envp));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->visible_env = FALSE;
	if (envp[0] == '_')
		new->index = -2;
	else
		new->index = -1;
	new->var = ft_strdup(envp);
	return (new);
}
