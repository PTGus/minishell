/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:15:36 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/10 16:08:50 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Initializes all the variables for the central struct.
 * @param central A struct that contains pointers to
 *  all the neccessary variables and lists.
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 */
void	init_central(t_central *central, t_envp **dupenv)
{
	t_envp	*tmp;

	tmp = *dupenv;
	central->dupenv = *dupenv;
	central->exit_val = 0;
	central->heredoc_paths = NULL;
	central->has_exited = FALSE;
	central->curr_cmd_idx = 0;
	central->curr_heredoc_idx = 0;
}
