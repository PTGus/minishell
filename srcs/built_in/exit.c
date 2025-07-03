/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:50:30 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/03 15:38:20 by gumendes         ###   ########.fr       */
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

/**
 * @brief Built-in function that behaves just like
 *  the "exit" command.
 */
void	ft_exit(t_central *central, t_input *cmd)
{
	if (cmd->next != NULL)
	{
		if (is_string_all_nums(cmd->next->value) == 1)
		{
			printf("exit\n");
			exit_err(cmd->next->value);
			central->exit_val = 2;
			central->has_exited = TRUE;
			return ;
		}
		else
		{
			printf("exit\n");
			central->exit_val = (ft_atoi(cmd->next->value) % 256);
			central->has_exited = TRUE;
			return ;
		}
	}
	printf("exit\n");
	central->exit_val = 0;
	central->has_exited = TRUE;
}
