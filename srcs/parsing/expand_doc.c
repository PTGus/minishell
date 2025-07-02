/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:17:03 by david-fe          #+#    #+#             */
/*   Updated: 2025/07/02 13:47:10 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief	Checks if str at i pos is $, has a value after
 * and is not inside '', and not immediately followed by a "
 * @return	0 if correct, 1 on malloc error
*/
int	ft_str_expand(t_central *central, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] == '$' && str[i + 1]
			&& ft_is_quoted(str, i) != 1
			&& (str[i + 1] != '\"'))
		{
			j = ft_get_expand_end(str, i + 1);
			if (ft_execute_expand(central, &str, i, j) == 1)
				return (1);
			i = 0;
		}
		else
			i++;
	}
	return (0);
}
