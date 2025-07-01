/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:50:30 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/01 16:37:35 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_string_all_nums(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	exit_err(char *str)
{
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

/**
 * @brief Built-in function that behaves just like
 *  the "exit" command.
 */
void	ft_exit(t_central *central, char *exit_val)
{
	if (exit_val != NULL)
	{
		if (is_string_all_nums(exit_val) == 1)
		{
			printf("exit\n");
			exit_err(exit_val);
			central->exit_val = 2;
			central->has_exited = TRUE;
			return ;
		}
		else
		{
			printf("exit\n");
			central->exit_val = (ft_atoi(exit_val) % 256);
			central->has_exited = TRUE;
			return ;
		}
	}
	printf("exit\n");
	central->exit_val = 0;
	central->has_exited = TRUE;
}
