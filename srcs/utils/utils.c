/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:04:40 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/01 14:39:17 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_exec_flags(t_input *cmd)
{
	char	**ret_arr;
	int		arg_amm;
	t_input	*start;
	t_input	*tmp;

	tmp = cmd;
	arg_amm = 0;
	while (tmp && tmp->token != ARGUMENT)
		tmp = tmp->next;
	start = tmp;
	while (tmp && tmp->token == ARGUMENT)
	{
		tmp = tmp->next;
		arg_amm++;
	}
	ret_arr = malloc(sizeof(char *) * (arg_amm + 1));
	ret_arr[arg_amm] = NULL;
	arg_amm = 0;
	while (start && start->token == ARGUMENT)
	{
		ret_arr[arg_amm] = start->value;
		arg_amm++;
		start = start->next;
	}
	return (ret_arr);
}

t_input	*find_cmd(t_input *cmd)
{
	t_input	*tmp;

	tmp = cmd;
	while (tmp->token != ARGUMENT)
		tmp = tmp->next;
	return (tmp);
}

void	has_shell_operator(t_central *central)
{

	if (to_pipe(central) != 0)
	{
		if (has_to_redirect(central, central->cmd[0]) == 2)
		 	return ;
		do_solo(central, central->cmd[0]);
	}
}

/**
 * @brief Compares 2 strings to check whether they are the same or not.
 * @return Returns 0 when the strings are equal, < 0 when the s1
 *  is of lower ascii value and > 0 when s1 is of higher ascii value.
 */
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void	increase_shlvl(t_envp **dupenv)
{
	t_envp	*tmp;
	int		tmp_val;

	tmp = ft_getenv(dupenv, "SHLVL");
	if (!tmp)
	{
		tmp = new_env("SHLVL=0");
		insert_before_last(dupenv, tmp);
		reorder_dupenv(dupenv);
		return ;
	}
	tmp_val = ft_atoi(tmp->value);
	tmp_val++;
	free(tmp->value);
	tmp->value = NULL;
	tmp->value = ft_itoa(tmp_val);
}
