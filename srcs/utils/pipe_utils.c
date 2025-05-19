/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:49:56 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/19 15:53:37 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	to_pipe(t_central *central, char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (ft_strcmp(split[i], "|") == 0)
			break ;
		i++;
	}
	if (split[i] != NULL)
	{
		piper(central, split, i);
		return(0);
	}
	return (i);
}
