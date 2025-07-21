/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:09:31 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/21 15:10:04 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Built-in command that behaves like echo, can work without
 *  flags or with the -n flag (no new line).
 * @param split An array of arrays with the prompt received from read line.
 */
void	ft_echo(t_central *central, t_input *cmd)
{
	t_input	*tmp;

	tmp = cmd;
	while (ft_strcmp(tmp->value, "echo") != 0)
		tmp = tmp->next;
	if (tmp->next == NULL)
		write(1, "\n", 1);
	else if ((ft_strcmp(tmp->next->value, "-n") == 0)
		&& (tmp->next->next == NULL))
		return (central->exit_val = 0, (void)0);
	else if (ft_strncmp(tmp->next->value, "-n", 2) == 0)
		echo_n(tmp->next);
	else
	{
		tmp = tmp->next;
		do_echo(tmp);
	}
	central->exit_val = 0;
}

void	do_echo(t_input *cmd)
{
	t_input	*tmp;
	int		first;

	tmp = cmd;
	first = 1;
	while (tmp)
	{
		if (tmp->token == ARGUMENT)
		{
			if (!first)
				write(1, " ", 1);
			ft_putstr_fd(tmp->value, 1);
			first = 0;
			tmp = tmp->next;
		}
		else
		{
			if (tmp->next)
				tmp = tmp->next->next;
			else
				break ;
		}
	}
	write(1, "\n", 1);
}

void	echo_n(t_input *cmd)
{
	t_input	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->token != ARGUMENT)
			break ;
		if (tmp->token == ARGUMENT)
			printf("%s", tmp->value);
		if (tmp->next != NULL && tmp->next->token == ARGUMENT)
			write(1, " ", 1);
		tmp = tmp->next;
	}
}
