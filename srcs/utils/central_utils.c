/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:15:36 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/01 16:36:04 by gumendes         ###   ########.fr       */
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
	central->exit_val = 0;
	central->curr_cmd = 0;
	central->dupenv = *dupenv;
	central->has_exited = FALSE;
}
