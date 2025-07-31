/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:42:47 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/31 12:25:47 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_cmd_valid(char *cmd)
{
	struct stat	sb;

	if (!cmd || ft_strcmp(cmd, "") == 0)
		return (1);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) != 0)
			return (4);
		if (stat(cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
			return (2);
		if (access(cmd, X_OK) != 0)
			return (3);
		return (0);
	}
	return (1);
}

static int	count_exec_flags(t_input *cmd)
{
	int		count;
	t_input	*tmp;

	count = 0;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->token != ARGUMENT)
		{
			if (tmp->next)
				tmp = tmp->next->next;
			else
				break ;
		}
		else
		{
			count++;
			tmp = tmp->next;
		}
	}
	return (count);
}

static void	fill_exec_flags(t_input *cmd, char **arr)
{
	int		i;
	t_input	*tmp;

	i = 0;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->token != ARGUMENT)
		{
			if (tmp->next)
				tmp = tmp->next->next;
			else
				break ;
		}
		else
		{
			arr[i] = ft_strdup(tmp->value);
			i++;
			tmp = tmp->next;
		}
	}
	arr[i] = NULL;
}

char	**get_exec_flags(t_input *cmd)
{
	char	**ret_arr;
	int		arg_amm;

	arg_amm = count_exec_flags(cmd);
	ret_arr = malloc(sizeof(char *) * (arg_amm + 1));
	if (!ret_arr)
		return (NULL);
	fill_exec_flags(cmd, ret_arr);
	return (ret_arr);
}
