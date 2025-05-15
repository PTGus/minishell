/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:11:52 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/15 13:55:03 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_input(char **split)
{
	int	i;
	int	fd;

	i = 0;
	while (split[i])
	{
		if (ft_strcmp(split[i], "<") == 0)
		{
			i++;
			fd = open(split[i], O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		i++;
	}
}

void	redirect_input(t_central *central, char **split)
{
	int	i;

	i = 0;
	(void)central;
	while (split[i])
	{
		if (split[i][0] == '<')
		{
			set_input(split + i);
			i++;
		}
		i++;
	}
}
