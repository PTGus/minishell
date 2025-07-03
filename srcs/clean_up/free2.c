/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:50:38 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/03 11:00:14 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	post_loop_cleanup(t_central *central, char *rl)
{
	free_central_cmd(central);
	free(rl);
}

void	free_input_list(t_input *head)
{
	t_input	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->value)
			free(head->value);
		free(head);
		head = tmp;
	}
}

void	free_central_cmd(t_central *central)
{
	int	i;

	if (!central->cmd)
		return ;
	i = 0;
	while (central->cmd[i])
	{
		free_input_list(central->cmd[i]);
		i++;
	}
	free(central->cmd);
	central->cmd = NULL;
}
