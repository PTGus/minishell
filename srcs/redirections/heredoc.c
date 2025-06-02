/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:56:03 by gumendes          #+#    #+#             */
/*   Updated: 2025/06/02 15:47:22 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// remember to check if prompt is quoted when you have the full project so you can call the expander accordingly
void	ft_heredoc(t_central *central, char *delimiter)
{
	int		fd;
	char	*rl_doc;

	fd = open(".heredoc_tmp",  O_CREAT | O_TRUNC | O_RDWR, 0644);
	while (1)
	{
		rl_doc = readline("> ");
		if (!rl_doc || ft_strcmp(rl_doc, delimiter) == 0)
			break ;
		ft_putendl_fd(rl_doc, fd);
		free(rl_doc);
	}
	if (!rl_doc)
	{
		bad_doc(delimiter);
		clean_doc(rl_doc);
		return ;
	}
	clean_doc(rl_doc);
	redirect_to_doc(fd);
}

void	redirect_to_doc(int fd)
{
	unlink(".heredoc_tmp");
	dup2(fd, STDIN_FILENO);
	close(fd);
}
