/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:07:30 by david-fe          #+#    #+#             */
/*   Updated: 2025/05/22 14:12:55 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_tokenizer(t_central *central)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = -1;
	str = NULL;
	while (central->pipe_matrix && central->pipe_matrix[++i])
	{
		j = -1;
		k = 0;
		while (central->pipe_matrix[i][++j])
		{
			if (central->pipe_matrix[i][j + 1] == ' '
					|| central->pipe_matrix[i][j + 1] == '\0')
			{
				str = ft_substr(central->pipe_matrix[i], k, (j - k + 1));
				printf("'%s'\n", str);
				k = j + 2;
				j++;
			}
		}
	}
}
