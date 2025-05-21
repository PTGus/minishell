/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:21:41 by david-fe          #+#    #+#             */
/*   Updated: 2025/05/19 15:22:19 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_redirect_check(char *str, int j)
{
	if (!str[j + 1])
		return (1);
	else if (str[j] == '>' && str[j + 1] == '<')
		return (1);
	else if (str[j] == str[j + 1] || (str[j] == '<' && str[j + 1] == '>'))
	{
		if (!str[j + 2] || str[j + 2] == '<' || str [j + 2] == '>')
			return (1);
	}
	return (0);
}

int	ft_are_redirects_invalid(t_central *central)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (central->pipe_matrix && central->pipe_matrix[++i])
	{
		while (central->pipe_matrix[i][++j])
		{
			if (ft_is_quoted(central->pipe_matrix[i], j) == 0
				&& ft_strchr("<>", central->pipe_matrix[i][j]))
			{
				if (ft_redirect_check(central->pipe_matrix[i], j) == 1)
					return (1);
			}
		}
		j = 0;
	}
	return (0);
}

int	ft_parse_redirects(t_central *central)
{
	if (ft_are_redirects_invalid(central) == 1)
		return (1);
	ft_space_redirects(central);
	return (0);
}
