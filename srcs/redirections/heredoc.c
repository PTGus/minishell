/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:56:03 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/03 11:27:12 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*treat_rl_doc(t_central *central ,char *rl_doc, int doc_type)
{
	if (doc_type == HERE_DOC)
		return (ft_check_expand_doc(central, rl_doc));
	else
		return (ft_strdup(rl_doc));
}

int	ft_heredoc(t_central *central, char *delimiter, int doc_type)
{
	int		fd;
	char	*tmp;
	char	*rl_doc;

	if (check_for_bad_redir(delimiter) == 1)
		return (2);
	setup_heredoc_signals();
	fd = open(".heredoc_tmp", O_CREAT | O_TRUNC | O_RDWR, 0644);
	tmp = NULL;
	while (1)
	{
		rl_doc = readline("> ");
		if (!rl_doc || ft_strcmp(rl_doc, delimiter) == 0)
			break ;
		if (g_signal == 130)
			return (clean_doc(rl_doc, tmp), 130);
		tmp = treat_rl_doc(central, rl_doc, doc_type);
		ft_putendl_fd(tmp, fd);
		clean_doc(rl_doc, tmp);
		tmp = NULL;
	}
	clean_doc(rl_doc, tmp);
	if (!rl_doc)
		return (redirect_to_doc(fd), bad_doc(delimiter), 0);
	return (redirect_to_doc(fd), 0);
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
