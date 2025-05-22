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

/**
 * @brief 
 * @param
 * @return
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
 * @brief 
 * @param
 * @return
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
 * @brief 
 * @param
 * @return
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
 * @brief 
 * @param
 * @return
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
