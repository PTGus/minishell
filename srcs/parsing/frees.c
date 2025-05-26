/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:32:39 by david-fe          #+#    #+#             */
/*   Updated: 2025/05/26 13:44:10 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Frees an array of strings
 * @param split Array of strings to free
 */
void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			split[i] = NULL;
			i++;
		}
	}
	if (split)
	{
		free(split);
		split = NULL;
	}
}

void	ft_free_list_err(t_central *central, char *str, t_input *current)
{
	int		i;
	t_input	*temp;
	t_input	*next;

	i = -1;
	if (str)
		free(str);
	if (current)
		free(current);
	while (central->cmd[++i])
	{
		temp = central->cmd[i];
		while (temp)
		{
			next = temp->next;
			free(temp->value);
			free(temp);
			temp = next;
		}
	}
	if (central->cmd)
		free(central->cmd);
}
