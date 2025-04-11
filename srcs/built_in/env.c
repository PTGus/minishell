/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:09:57 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/11 15:38:50 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Built-in function that behaves just like the env command, prints all the current environmental variables.
 */
void	ft_env(t_envp **dupenv)
{
	t_envp	*tmp;

	tmp = *(dupenv);
	if (getenv("PATH") == NULL)
	{
		printf("bash: env: No such file or directory\n");
		return ;
	}
	else
	{
		while (tmp->next != NULL)
		{
			printf("%s%s\n", tmp->var, tmp->value);
			tmp = tmp->next;
		}
		printf("_=/usr/bin/env\n");
	}
}

/**
 * @brief Creates a new node with the given value.
 * @param nbr The value that this new node will assume.
 * @return The new node.
 */
t_envp	*new_env(char *envp)
{
	t_envp	*new;
	int		i;

	new = ft_calloc(1, sizeof(t_envp));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	i = 0;
	while (envp[i] != '=')
		i++;
	new->var = ft_strdup(ft_substr(envp, 0, i + 1));
	new->value = ft_strdup(envp + (1 + i));
	return (new);
}

/**
 * @brief Creates all necessary nodes to populate the
 *  t_envp list with all the environmental variables.
 * @param dupenv The main stack and head.
 * @param count The ammount of nodes to create.
 * @return On success: 0.
 *
 * On failure: 1.
 */
int init_env(t_envp **dupenv, char **envp)
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
		curr = new_env(envp[i]);
		if (!curr)
			return (1);
		ft_lst_back(dupenv, curr);
		i++;
	}
	return (0);
}

int duplicate_env(t_envp **dupenv, char **envp)
{
	if (init_env(dupenv, envp) == 1)
		return (1);
	return (0);
}
