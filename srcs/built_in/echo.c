/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:09:31 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/11 12:17:04 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Built-in command that behaves like echo, can work without flags or with the -n flag (no new line).
 * @param split The command flag (if available) and what to write.
 */
void	ft_echo(char **split)
{
	int	i;

	if (ft_strncmp(split[1], "-n", 2) == 0)
	{
		i = 2;
		while (split[i])
		{
			printf("%s", split[i]);
			if (split[i + 1] != NULL)
				printf(" ");
			i++;
		}
	}
	else
	{
		i = 1;
		while (split[i])
		{
			printf("%s", split[i]);
			if (split[i + 1] != NULL)
				printf(" ");
			i++;
		}
		printf("\n");
	}
}
