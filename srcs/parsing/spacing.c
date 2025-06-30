/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spacing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:10:09 by david-fe          #+#    #+#             */
/*   Updated: 2025/06/30 16:32:48 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Allocates an array to accomodate respaced commands,
 *  removing at edges and extras
 * @return 0 if no issues, >0 on malloc error
 */
int	ft_remove_extra_spaces(t_central *central)
{
	int		i;
	int		flag;
	char	**new_split;
	char	**temp;

	i = -1;
	flag = 0;
	new_split = malloc((central->matrix_len + 1) * sizeof(char *));
	if (!new_split)
		return (1);
	while (central->pipe_matrix && central->pipe_matrix[++i])
	{
		new_split[i] = malloc((ft_new_spaced_len(central->pipe_matrix[i]) + 1)
				* sizeof(char));
		if (!new_split[i])
			return (ft_free_split(new_split), 2);
	}
	i = 0;
	while (central->pipe_matrix && central->pipe_matrix[i])
		ft_assign_new_split(new_split, central->pipe_matrix, i++);
	new_split[central->matrix_len] = NULL;
	temp = central->pipe_matrix;
	central->pipe_matrix = new_split;
	ft_free_split(temp);
	return (0);
}

/**
 * @brief	Takes a string and counts len excluding starting, ending and
 * extra spaces, except quoted spaces
 * @param	String to count
 * @return	New len value
 */
int	ft_new_spaced_len(char *command)
{
	int	j;
	int	flag;
	int	len;

	j = -1;
	len = 0;
	flag = 0;
	while (command && command[++j] && ft_rest_is_space(command, j) == 0)
	{
		if (command[j] != ' '
			|| (ft_is_quoted(command, j) != 0 && command[j] == ' '))
		{
			len++;
			flag = 1;
		}
		else if (flag == 1 && command[j] == ' ')
		{
			len++;
			flag = 0;
		}
	}
	return (len);
}

/**
 * @brief	Assigns the new string skipping extra spaces
 * @param	new_split - newly alloc'ed split to assign
 * @param	matrix - previous matrix, to copy from
 * @param	i - passed for singling out one string at a time
 */
void	ft_assign_new_split(char **new_split, char **matrix, int i)
{
	int	j;
	int	k;
	int	flag;

	j = -1;
	k = 0;
	flag = 0;
	while (matrix[i][++j] && ft_rest_is_space(matrix[i], j) == 0)
	{
		if (matrix[i][j] != ' ' ||
			(ft_is_quoted(matrix[i], j) != 0 &&
			matrix[i][j] == ' '))
		{
			new_split[i][k] = matrix[i][j];
			k++;
			flag = 1;
		}
		else if (flag == 1 && matrix[i][j] == ' ')
		{
			new_split[i][k] = ' ';
			k++;
			flag = 0;
		}
	}
	new_split[i][k] = '\0';
}

/**
 * @brief	Iterates string to check if rest is space
 * @param	str - string to check
 * @return	1 all space, 0 if non-space is found
 */
int	ft_rest_is_space(char *str, int j)
{
	while (str && str[j])
	{
		if (str[j] != ' ')
			return (0);
		j++;
	}
	return (1);
}
