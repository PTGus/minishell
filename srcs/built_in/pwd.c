/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:50:00 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/08 13:17:45 by gumendes         ###   ########.fr       */
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
	char	*cwd;

	tmp = ft_getenv(&central->dupenv, "PWD");
	if (!tmp)
	{
		cwd = getcwd(NULL, 0);
		write(1, cwd, ft_strlen(cwd));
		free(cwd);
	}
	else
		printf("%s\n", tmp->value);
	central->exit_val = 0;
}
