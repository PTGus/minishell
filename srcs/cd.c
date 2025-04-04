/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:14:43 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/04 16:09:49 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(char **split, char *home_path)
{
	if (split[1] == NULL || (split[1][0] == '~' && split[1][1] =='\0'))
	{
		chdir(home_path);
		return ;
	}
	if (access(split[1], X_OK) < 0)
		printf("bash: cd: %s: No such file or directory\n", split[1]);
	else
		chdir(split[1]);
}
