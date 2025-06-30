/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:09:57 by gumendes          #+#    #+#             */
/*   Updated: 2025/06/25 11:08:14 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Built-in function that behaves just like
 *  the env command, prints all the current environmental variables.
 */
void	ft_env(t_central *central, char **split)
{
	t_envp	*tmp;

	tmp = central->dupenv;
	while (tmp && ft_strcmp(tmp->var, "PATH") != 0)
		tmp = tmp->next;
	if (!tmp)
		return (central->exit_val = 127, (void)0);
	if (split[1] != NULL)
	{
		central->exit_val = 1;
		return (ft_putstr_fd("invalid arguments\n", 2), (void)0);
	}
	tmp = central->dupenv;
	while (tmp != NULL)
	{
		if (tmp->visible_env == TRUE)
		{
			if (tmp->value == NULL)
				printf("%s=\n", tmp->var);
			else
				printf("%s=%s\n", tmp->var, tmp->value);
		}
		tmp = tmp->next;
	}
	central->exit_val = 0;
}

/**
 * @brief Creates a new node with the given value.
 * @param nbr The value that this new node will assume.
 * @return The new node.
 */
t_envp	*new_env(char *envp)
{
	t_envp	*new;
	char	*tmp;
	int		i;

	new = ft_calloc(1, sizeof(t_envp));
	if (!new)
		return (NULL);
	new->value = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->visible_env = TRUE;
	new->has_equal = TRUE;
	if (envp[0] == '_')
		new->index = -2;
	else
		new->index = -1;
	i = 0;
	while (envp[i] != '=')
		i++;
	tmp = ft_substr(envp, 0, i);
	new->var = ft_strdup(tmp);
	free(tmp);
	if (envp[i + 1] >= 33 && envp[i + 1] <= 126)
		new->value = ft_strdup(envp + (1 + i));
	return (new);
}

/**
 * @brief Creates all necessary nodes to populate the
 *  t_envp list with all the environmental variables.
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 * @param envp The environmental variables received through the main.
 * @return On success: 0.
 *
 * On failure: 1.
 */
int	init_env(t_envp **dupenv, char **envp)
{
	t_envp	*curr;
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (envp[count])
		count++;
	while (i < count)
	{
		if (i + 1 == count)
			curr = new_env("_=/usr/bin/env");
		else
			curr = new_env(envp[i]);
		if (!curr)
			return (1);
		ft_lst_back(dupenv, curr);
		i++;
	}
	return (0);
}

/**
 * @brief Initializes and the dupenv list's nodes and then
 *  assigns them a number according to ascending ASCII order.
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 * @param envp The environmental variables received through the main.
 * @return On success: 0.
 *
 * On failure: 1.
 */
int	duplicate_env(t_envp **dupenv, char **envp)
{
	if (init_env(dupenv, envp) == 1)
		return (1);
	organise_env(dupenv);
	return (0);
}
