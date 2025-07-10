/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:09:57 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/10 16:15:49 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Built-in function that behaves just like
 *  the env command, prints all the current environmental variables.
 */
void	ft_env(t_central *central, t_input *cmd)
{
	t_envp	*tmp_env;
	t_input	*tmp_cmd;

	tmp_env = ft_getenv(&central->dupenv, "PATH");
	tmp_cmd = cmd;
	if (!tmp_env)
		return (central->exit_val = 127, not_dir("env"),(void)0);
	while (ft_strcmp(tmp_cmd->value, "env") != 0)
		tmp_cmd = tmp_cmd->next;
	if (tmp_cmd->next != NULL)
		return (ft_putstr_fd("Invalid arguments\n", 2),
			central->exit_val = 1, (void)0);
	tmp_env = central->dupenv;
	while (tmp_env != NULL)
	{
		if (tmp_env->visible_env == TRUE)
		{
			if (tmp_env->value == NULL)
				printf("%s=\n", tmp_env->var);
			else
				printf("%s=%s\n", tmp_env->var, tmp_env->value);
		}
		tmp_env = tmp_env->next;
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

	new = malloc(1 * sizeof(t_envp));
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
	while (envp[i] != '=' && envp[i] != '+')
		i++;
	if (envp[i] == '+')
		i++;
	tmp = ft_substr(envp, 0, i);
	if (envp[i + 1] >= 33 && envp[i + 1] <= 126)
		new->value = ft_strdup(envp + (1 + i));
	return (new->var = ft_strdup(tmp), free(tmp), new);
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
