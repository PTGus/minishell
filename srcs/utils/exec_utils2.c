/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:42:47 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/08 17:10:20 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_cmd_valid(char *cmd)
{
	struct stat	sb;
	int	i;

	i = 0;
	if (!cmd)
		return (1);
	if (ft_strcmp(cmd, "") == 0)
		return (1);
	if (access(cmd, F_OK) == 0)
	{
		if (stat(cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
			return (2);
		else
			return (3);
	}
	return (0);
}
