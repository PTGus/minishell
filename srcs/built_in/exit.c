/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:50:30 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/23 13:07:36 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_string_all_nums(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0') // sign alone is not valid
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	exit_err(char *str)
{
	int		err_len;
	char	*err_msg;
	char	*tmp;

	err_msg = "bash: exit: ";
	err_msg = ft_strjoin(err_msg, str);
	tmp = err_msg;
	err_msg = ft_strjoin(tmp, ": numeric argument required\n");
	free(tmp);
	err_len = ft_strlen(err_msg);
	write(2, err_msg, err_len);
	free(err_msg);
}

void	special_exit(t_central *central, t_input *cmd)
{
	if (!cmd)
	{
		ft_putstr_fd("exit\n", 2);
		central->exit_val = 0;
		central->has_exited = TRUE;
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		excessive_args("exit");
		central->exit_val = 1;
	}
}

int	is_within_bounds(char *exit_val)
{
	if (exit_val[0] == '-')
		return (is_under_min(exit_val));
	return (is_over_max(exit_val));
}

/**
 * @brief Built-in function that behaves just like
 *  the "exit" command.
 */
void	ft_exit(t_central *central, t_input *cmd)
{
	if (ft_strcmp(cmd->next->value, "--") == 0)
	{
		central->has_exited = TRUE;
		return (central->exit_val = 0, ft_putstr_fd("exit\n", 2), (void) 0);
	}
	if (is_string_all_nums(cmd->next->value) == 1
		|| is_within_bounds(cmd->next->value) != 0)
	{
		ft_putstr_fd("exit\n", 2);
		exit_err(cmd->next->value);
		central->has_exited = TRUE;
		return (central->exit_val = 2, (void) 0);
	}
	else if (cmd->next->next == NULL)
	{
		ft_putstr_fd("exit\n", 2);
		central->exit_val = (ft_atoi(cmd->next->value) % 256);
		central->has_exited = TRUE;
		return ;
	}
	special_exit(central, cmd->next);
}
