/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:29:49 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/09 17:15:25 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_envp	*new_node(void);
static t_envp	*lstlast(t_envp *lst);
static void		ft_lst_back(t_envp **dupenv, t_envp *curr);

/**
 * @brief Creates all necessary nodes to populate the
 *  t_envp list with all the environmental variables.
 * @param dupenv The main stack and head.
 * @param count The ammount of nodes to create.
 * @return On success: 0.
 *
 * On failure: 1.
 */
int init_env(t_envp **dupenv, int count)
{
    t_envp	*curr;
    int		i;

    *dupenv = NULL;
    i = 0;
    while (i <= count)
    {
        curr = new_node();
        if (!curr)
            return (1);
        ft_lst_back(dupenv, curr);
        i++;
    }
    return (0);
}


int	populate_env(t_envp **dupenv, char **envp)
{
	int	i;
	int	j;
	t_envp	*temp;

	i = 0;
	temp = *dupenv;
	while (envp[i])
	{
		j = 0;
		while (1)
		{
			j++;
			if (envp[i][j] == '=')
			{
				temp->var = ft_strdup(ft_substr(envp[i], 0, j));
				if (!temp->var)
					return (1);
				break ;
			}
		}
		temp->value = ft_strdup(envp[i] + 1 + j);
		if (!temp->value)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Creates a new node with the given value.
 * @param nbr The value that this new node will assume.
 * @return The new node.
 */
static t_envp	*new_node(void)
{
	t_envp	*new;

	new = ft_calloc(1, sizeof(t_envp));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->var = NULL;
	new->value = NULL;
	return (new);
}

/**
 * @brief Adds a node to the end of the list, updates the head if necessary.
 */
static void	ft_lst_back(t_envp **dupenv, t_envp *curr)
{
    t_envp *last;

    if (!*dupenv)
    {
        *dupenv = curr;
        return;
    }
    last = lstlast(*dupenv);
    last->next = curr;
    curr->prev = last;
}

/** @brief Gets last element of the list.
 *  @param lst  The list.
 * 	@return The last element of the list.
*/
static t_envp	*lstlast(t_envp *dupenv)
{
	t_envp	*temp;

	temp = dupenv;
	if (!temp)
		return (NULL);
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}
