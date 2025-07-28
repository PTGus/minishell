/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:09:31 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/21 16:04:27 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_flag(char *to_check)
{
	int	i;

	if (to_check[0] != '-' || to_check[1] != 'n')
		return (1);
	i = 2;
	while (to_check[i])
	{
		if (to_check[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Built-in command that behaves like echo, can work without
 *  flags or with the -n flag (no new line).
 * @param split An array of arrays with the prompt received from read line.
 */
void	ft_echo(t_central *central, t_input *cmd)
{
	t_input	*tmp;
	int		flag;

	tmp = cmd;
	while (tmp && ft_strcmp(tmp->value, "echo") != 0)
		tmp = tmp->next;
	if (!tmp || !tmp->next)
	{
		write(1, "\n", 1);
		central->exit_val = 0;
		return;
	}
	tmp = tmp->next;
	flag = 0;
	while (tmp && check_flag(tmp->value) == 0)
	{
		flag = 1;
		tmp = tmp->next;
	}
	do_echo(tmp);
	if (!flag)
		write(1, "\n", 1);
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
}

void	echo_n(t_input *cmd)
{
	t_input	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->token != ARGUMENT && tmp->token != DELETE)
			break ;
		if (tmp->token == ARGUMENT)
			printf("%s", tmp->value);
		if (tmp->next != NULL && tmp->next->token == ARGUMENT)
			write(1, " ", 1);
		tmp = tmp->next;
	}
}
