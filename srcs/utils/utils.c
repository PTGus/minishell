/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:04:40 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/09 16:05:08 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_input	*find_cmd(t_input *cmd)
{
	t_input	*tmp;

	tmp = cmd;
	while (tmp->token != ARGUMENT)
		tmp = tmp->next->next;
	return (tmp);
}

void	has_shell_operator(t_central *central)
{
	if (to_pipe(central) != 0)
	{
		if (has_to_redirect(central, central->cmd[0]) != 0)
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
