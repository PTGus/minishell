/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:05:25 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/23 11:18:51 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	plus_export(t_central *central, char *exportion)
{
	t_envp	*var;
	char	*tmp;
	int		i;

	i = 0;
	while (exportion[i] && exportion[i] != '+')
		i++;
	tmp = ft_substr(exportion, 0, i);
	var = ft_getenv(&central->dupenv, tmp);
	free(tmp);
	if (!var)
	{
		var = new_env(exportion);
		insert_before_last(&central->dupenv, var);
		return (1);
	}
	trunc_export(var, exportion, i);
	return (1);
}

int	is_special_exportion(t_central *central, char *exportion)
{
	int	i;

	i = 0;
	if (ft_isalpha(exportion[0]) == 0)
		return (bad_export(exportion), 2);
	if (validity_check(exportion) == 1)
		return (bad_export(exportion), 2);
	while (exportion[i])
	{
		if (exportion[i] == '=' || exportion[i] == '+')
			break ;
		i++;
	}
	if (exportion[i] == '+' && exportion[i + 1] == '=')
		return (plus_export(central, exportion), 1);
	else if (exportion[i] == '=' && exportion[i + 1] == '\0')
		return (hidden_export(central, exportion, TRUE), 1);
	else if (exportion[i] != '=')
		return (hidden_export(central, exportion, FALSE), 1);
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

void	hidden_export(t_central *central, char *exportion, int has_equal)
{
	t_envp	*new;

	if (should_revalue(&central->dupenv, exportion) == 0)
	{
		new = new_valuesless_env(exportion);
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

	new = malloc(1 * sizeof(t_envp));
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
