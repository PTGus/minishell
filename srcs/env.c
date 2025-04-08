/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:09:57 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/07 16:44:32 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(char **env)
{
	int	i;

	if (getenv("PATH") == NULL)
	{
		printf("bash: env: No such file or directory\n");
		return ;
	}
	else
	{
		i = 0;
		while (env[i + 1] != NULL)
		{
			printf("%s\n", env[i]);
			i++;
		}
		printf("_=/usr/bin/env\n");
	}
}
