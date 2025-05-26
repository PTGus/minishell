/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:04:40 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/26 15:41:55 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	has_shell_operator(t_central *central, char **split)
{
	if (to_pipe(central, split) == 0)
		return ;
	else
		do_cmd(central, split);
}

/**
 * @brief Compares 2 strings to check whether they are the same or not.
 * @return Returns 0 when the strings are equal, < 0 when the s1
 *  is of lower ascii value and > 0 when s1 is of higher ascii value.
 */
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
