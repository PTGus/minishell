/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:55:35 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/27 17:17:53 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_to_redirect(char **split)
{
	static int	i;

	while (split[i])
	{
		if (ft_strcmp(split[i], "|") == 0)
		{
			i++;
			break ;
		}
		if (ft_strcmp(split[i], "<") == 0 | ft_strcmp(split[i], "<<") == 0
			| ft_strcmp(split[i], ">") == 0 | ft_strcmp(split[i], ">>") == 0)
		{
			set_redirections(split);
			return (0);
		}
		i++;
	}
	return (1);
}

int	set_redirections(char **split)
{
	static int	i;

	while (split[i])
	{
		if (ft_strcmp(split[i], "|") == 0)
		{
			i++;
			break ;
		}
		if (ft_strcmp(split[i], "<") == 0 | ft_strcmp(split[i], "<<") == 0
			| ft_strcmp(split[i], ">") == 0 | ft_strcmp(split[i], ">>") == 0)
		{
			if (do_redirection(split, i) == 1)
			{
				printf("Invalid redirection\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	do_redirection(char **split, int index)
{
	if (ft_strcmp(split[index], "<") == 0)
		return (set_input(split[index + 1]));
	else if (ft_strcmp(split[index], ">") == 0)
		return (set_output(split[index + 1]));
	// else if (ft_strcmp(split[index], "<<") == 0)
	// 	return (heredoc(split[index + 1]));
	// else if (ft_strcmp(split[index], ">>") == 0)
	// 	return (set_output(split[index + 1]));
	return (1);
}
