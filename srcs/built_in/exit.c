/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:50:30 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/07 15:18:28 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Built-in function that behaves just like
 *  the "exit" command.
 */
void	ft_exit(t_central *central, char *exit_val)
{
	int i;

	clean_all(central);
	i = 0;
	if (exit_val != NULL)
	{
		while (exit_val[i])
		{
			if (ft_isdigit(exit_val[i]) == 0)
			{
				printf("exit\n");
				printf("bash: exit: %s: numeric argument required\n", exit_val);
				exit(2);
			}
			i++;
		}
		if (exit_val[i] == '\0')
		{
			printf("exit\n");
			exit(ft_atoi(exit_val) % 256);
		}
	}
	printf("exit\n");
	exit(0);
}
