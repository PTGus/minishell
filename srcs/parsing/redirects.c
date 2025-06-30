/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:21:41 by david-fe          #+#    #+#             */
/*   Updated: 2025/06/30 16:32:47 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief	Caller function for adding space to unspaced redirects < > << >>
 * @param	to_space - Amount of extra spaces to allocate for 
 * @return	0 all correct, >0 on invalid redirects or malloc errors
 */
int	ft_space_redirects(t_central *central)
{
	int	i;
	int	j;
	int	to_space;

	if (ft_are_redirects_invalid(central) == 1)
		return (1);
	i = -1;
	j = -1;
	while (central->pipe_matrix && central->pipe_matrix[++i])
	{
		to_space = 0;
		while (central->pipe_matrix[i][++j])
			to_space = ft_count_unspaced_redirects(
					central->pipe_matrix[i], j, to_space);
		if (to_space > 0)
		{
			central->pipe_matrix[i] = ft_realloc_redir_str(
					central->pipe_matrix[i], to_space);
			if (!central->pipe_matrix[i])
				return (1);
		}
		j = -1;
	}
	return (0);
}

/**
 * @brief	Iterates through the matrix, on finding < or >
 * calls for a validity check
 * @return	0 all correct, 1 if redirect_check return error
 */
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

/**
 * @brief	Checks for illegal combinations for redirs <<, >>, <>, >>>, <<<
 * and for redirects at the end, erroring
 * @param	str - String to check for valid redirects
 * @param	j - Position of previously found '<' or '>'
 * @return	0 if valid redirect, 1 otherwise
 */
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

/**
 * @brief	Counts how many extra spaces are needed for the redirects
 * @param	str - String to check at position j
 * @param	extra_space - continuously receives and updates amount of 
 * needed space
 * @return	Amount of extra spaces needed
 */
int	ft_count_unspaced_redirects(char *str, int j, int extra_space)
{
	if (str[j + 1])
	{
		if (((ft_strchr("<>", str[j]) && !ft_is_quoted(str, j))
				&& !ft_strchr("< >", str[j + 1])) || (!ft_strchr("< >", str[j])
				&& (ft_strchr("<>", str[j + 1]) && !ft_is_quoted(str, j + 1))))
			extra_space++;
	}
	return (extra_space);
}

/**
 * @brief	Allocates and assigns spaced version of the string
 * @param	str - pipe being currently respaced
 * @return	Newly alloc'ed, spaced string
*/
char	*ft_realloc_redir_str(char *str, int to_space)
{
	char	*new_str;
	int		new_len;
	int		j;
	int		k;

	j = -1;
	k = -1;
	new_len = ft_strlen(str) + to_space;
	new_str = malloc((new_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	while (str[++k])
	{
		if (ft_count_unspaced_redirects(str, k, 0) == 1)
		{
			new_str[++j] = str[k];
			new_str[++j] = ' ';
		}
		else
			new_str[++j] = str[k];
	}
	new_str[++j] = '\0';
	free(str);
	str = NULL;
	return (new_str);
}
