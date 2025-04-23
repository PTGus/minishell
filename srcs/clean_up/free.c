/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:55:17 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/23 17:09:57 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_envdelone(t_envp *dupenv)
{
	if (!dupenv)
		return ;
	free(dupenv->var);
	free(dupenv->value);
	free(dupenv);
}

void	free_env(t_envp **dupenv)
{
	t_envp	*tmp;

	while (*dupenv != NULL)
	{
		tmp = (*dupenv)->next;
		ft_envdelone(*dupenv);
		*dupenv = tmp;
	}
}
