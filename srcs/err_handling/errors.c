/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:46:42 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/09 15:14:35 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief A error message for when a command is not found.
 */
void	comm_not_foud(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
}

/**
 * @brief A error message for when the specified
 *  file/folder is not found.
 */
void	not_dir(char *str)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
