/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:09:31 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/09 15:14:35 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Built-in command that behaves like echo, can work without
 *  flags or with the -n flag (no new line).
 * @param split An array of arrays with the prompt received from read line.
 */
void	ft_echo(char **split, t_central *central)
{
	int	i;

	if (ft_strncmp(split[1], "-n", 2) == 0)
	{
		i = 1;
		while (split[++i])
		{
			printf("%s", split[i]);
			if (split[i + 1] != NULL)
				write(1, " ", 1);
		}
	}
	else
	{
		i = 0;
		while (split[++i])
		{
			printf("%s", split[i]);
			if (split[i + 1] != NULL)
				write(1, " ", 1);
		}
		printf("\n");
	}
	central->exit_val = 0;
}
