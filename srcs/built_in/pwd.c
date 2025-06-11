/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:50:00 by gumendes          #+#    #+#             */
/*   Updated: 2025/06/11 11:21:02 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Built-in function that behaves just like
 *  the "pwd" command.
 */
void	ft_pwd(t_central *central)
{
	t_envp	*tmp;

	tmp = ft_getenv(&central->dupenv, "PWD");
	printf("%s\n", tmp->value);
	central->exit_val = 0;
}
