/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:56:03 by gumendes          #+#    #+#             */
/*   Updated: 2025/06/04 11:48:34 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// remember to check if prompt is quoted when you have the full project so you can call the expander accordingly
int	ft_heredoc(char *delimiter)
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
	clean_doc(rl_doc);
	if (!rl_doc)
	{
		bad_doc(delimiter);
		return (1);
	}
	redirect_to_doc(fd);
	return (0);
}

void	redirect_to_doc(int fd)
{
	int	fd_tmp;

	close(fd);
	fd_tmp = open(".heredoc_tmp", O_RDONLY, 0644);
	unlink(".heredoc_tmp");
	dup2(fd_tmp, STDIN_FILENO);
	close(fd_tmp);
}
