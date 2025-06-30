/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:21:14 by david-fe          #+#    #+#             */
/*   Updated: 2025/06/30 16:32:46 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Prints an array of strings for debugging
 * @param str_arr Array of strings to print
 */
void	ft_print_arr(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr && str_arr[i])
	{
		printf("%d: '%s'\n", i, str_arr[i]);
		i++;
	}
}

void	ft_print_list_array(t_input **array)
{
	int		i;
	t_input	*temp;

	i = -1;
	while (array[++i])
	{
		temp = array[i];
		while (temp)
		{
			printf("l%i:%s(t:%i)\n", temp->index, temp->value, temp->token);
			temp = temp->next;
		}
		printf("\n");
	}
}
