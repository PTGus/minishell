/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:55:35 by gumendes          #+#    #+#             */
/*   Updated: 2025/06/04 10:49:31 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_to_redirect(t_central *central, char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (ft_strcmp(split[i], "<") == 0 || ft_strcmp(split[i], "<<") == 0
			|| ft_strcmp(split[i], ">") == 0 || ft_strcmp(split[i], ">>") == 0)
			return (set_redirections(central, split));
		i++;
	}
	return (1);
}

int	set_redirections(t_central *central, char **split)
{
	int			i;

	i = 0;
	while (split[i])
    {
        if (!ft_strcmp(split[i], "<")  || !ft_strcmp(split[i], "<<") ||
            !ft_strcmp(split[i], ">")  || !ft_strcmp(split[i], ">>"))
        {
            if (do_redirection(split, i) == 2)
			{
				central->exit_val = 1;
                return (1);
			}
            i++;
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
	else if (ft_strcmp(split[index], "<<") == 0)
		return (ft_heredoc(split[index + 1]));
	else if (ft_strcmp(split[index], ">>") == 0)
		return (append_redir(split[index + 1]));
	return (1);
}
