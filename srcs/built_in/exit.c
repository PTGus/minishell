/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:50:30 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/09 14:25:25 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_string_all_nums(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0)
		{
			if (str[i] != '+' && str[i] != '-' && ft_isdigit(str[i]) == 0)
				return (1);
			i++;
		}
		if (i > 0 && ft_isdigit(str[i]) == 0)
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
		printf("exit\n");
		central->exit_val = 0;
		central->has_exited = TRUE;
	}
	else
	{
		printf("exit\n");
		excessive_args("exit");
		central->exit_val = 1;
	}
}

int	is_within_bounds(char *exit_val)
{
	char	*check;
	int		len;

	len = ft_strlen(exit_val);
	if (exit_val[0] == '-')
	{
		check = "-9223372036854775808";
		if (len > 20)
		return (1);
		if (len < 20)
		return (0);
		if (ft_strcmp(exit_val, check) > 0)
		return (1);
	}
	else
	{
		check = "9223372036854775807";
		if (len > 19)
			return (1);
		if (len < 19)
			return (0);
		if (ft_strcmp(exit_val, check) > 0)
			return (1);
	}
	return (0);
}


/**
 * @brief Built-in function that behaves just like
 *  the "exit" command.
 */
void	ft_exit(t_central *central, t_input *cmd)
{
	if (cmd->next != NULL && cmd->next->next == NULL)
	{
		if (ft_strcmp(cmd->next->value, "--") == 0)
		{
			central->has_exited = TRUE;
			return (central->exit_val = 0, printf("exit\n"), (void) 0);
		}
		if (is_string_all_nums(cmd->next->value) == 1
			|| is_within_bounds(cmd->next->value) != 0)
		{
			exit_err(cmd->next->value);
			central->has_exited = TRUE;
			return (central->exit_val = 2, printf("exit\n"), (void) 0);
		}
		else
		{
			printf("exit\n");
			central->exit_val = (ft_atoi(cmd->next->value) % 256);
			central->has_exited = TRUE;
			return ;
		}
	}
	else
		special_exit(central, cmd->next);
}
