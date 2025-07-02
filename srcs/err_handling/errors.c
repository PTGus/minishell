/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:46:42 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/02 12:49:26 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	bad_export(char *str)
{
	ft_putstr_fd("bash: export: \'", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

void	bad_doc(char *str)
{
	ft_putstr_fd("bash: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("')", 2);
}

void	no_perms(char *str)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": Permission denied", 2);
}

/**
 * @brief A error message for when a command is not found.
 */
void	comm_not_found(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": command not found", 2);
}

/**
 * @brief A error message for when the specified
 *  file/folder is not found.
 */
void	not_dir(char *str)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": No such file or directory", 2);
}
