/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spacing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:10:09 by david-fe          #+#    #+#             */
/*   Updated: 2025/05/15 17:10:53 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_space(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int	ft_spaced_len(char *command)
{
	int	j;
	int	flag;
	int	len;

	j = -1;
	len = 0;
	flag = 0;
	while (command && command[++j])
	{
		if (!ft_is_space(command[j]))
		{
			len++;
			flag = 1;
		}
		else if (flag == 1 && ft_is_space(command[j]) == 1)
			flag = 0;
	}
	return (len);
}

char	**ft_remove_extra_spaces(char **split)
{
	int		i;
	int		j;
	int		flag;
	char	**new_split;

	i = -1;
	j = -1;
	flag = 0;
	new_split = malloc(sizeof(char *));
	while (split && split[++i])
		new_split[i] = malloc((ft_spaced_len(split[i]) + 1) * sizeof(char *));
	i = -1;
	while (split && split[++i])
	{
		while (split[i][++j])
		{
			printf("placeholder");
		}
	}
	new_split = NULL;
	return (new_split);
}
// NEED TO KNOW SPLIT LEN for new_split malloc
