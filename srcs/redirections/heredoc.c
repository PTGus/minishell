/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:56:03 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/02 13:24:28 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// remember to check if prompt is quoted when you have the full project so you can call the expander accordingly
int	ft_heredoc(t_central *central, char *delimiter, int doc_type)
{
	int		fd;
	char	*rl_doc;

	if (check_for_bad_redir(delimiter) == 1)
		return (2);
	setup_heredoc_signals();
	fd = open(".heredoc_tmp", O_CREAT | O_TRUNC | O_RDWR, 0644);
	while (1)
	{
		rl_doc = readline("> ");
		if (!rl_doc || ft_strcmp(rl_doc, delimiter) == 0)
			break ;
		if (g_signal == 130)
			return (130);
		ft_putendl_fd(rl_doc, fd);
		free(rl_doc);
	}
	clean_doc(rl_doc);
	if (!rl_doc)
		return (unlink(".heredoc_tmp"), close(fd), bad_doc(delimiter), 0);
	redirect_to_doc(fd);
	return (0);
}

void	redirect_to_doc(int fd)
{
	int	fd_tmp;

	close(fd);
	fd_tmp = open(".heredoc_tmp", O_RDONLY);
	if (fd_tmp == -1)
	{
		perror("open .heredoc_tmp");
		exit(1);
	}
	if (unlink(".heredoc_tmp") == -1)
		perror("unlink .heredoc_tmp");
	if (dup2(fd_tmp, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(fd_tmp);
}
