/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:56:03 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/23 12:07:13 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_doc_name(int cmd_idx, int heredoc_idx)
{
	char	*doc_name;
	char	*tmp;
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_itoa(cmd_idx);
	if (!tmp1)
		return (perror("malloc"), NULL);
	tmp2 = ft_itoa(heredoc_idx);
	if (!tmp2)
		return (free(tmp1), perror("malloc"), NULL);
	doc_name = ft_strjoin(".heredoc_tmp", tmp1);
	tmp = doc_name;
	doc_name = ft_strjoin(doc_name, "_");
	free(tmp);
	tmp = doc_name;
	doc_name = ft_strjoin(doc_name, tmp2);
	free(tmp);
	free(tmp1);
	free(tmp2);
	if (!doc_name)
		return (perror("malloc"), NULL);
	return (doc_name);
}

static int	doc_prep(t_central *central, char *delimiter,
	int cmd_idx, int heredoc_idx)
{
	int		fd;

	if (check_for_bad_redir(delimiter) == 1)
		return (-2);
	setup_heredoc_signals();
	central->heredoc_paths[cmd_idx][heredoc_idx]
		= get_doc_name(cmd_idx, heredoc_idx);
	fd = open(central->heredoc_paths[cmd_idx][heredoc_idx],
			O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}

static void	treat_rl_doc(t_central *central, char *rl_doc, int doc_type, int fd)
{
	char	*tmp;

	if (doc_type == HERE_DOC)
	{
		tmp = ft_check_expand_doc(central, rl_doc);
		write(fd, tmp, ft_strlen(tmp));
		free(tmp);
	}
	else
		write(fd, rl_doc, ft_strlen(rl_doc));
}

int	redirect_doc_path(char **path)
{
	int	fd;

	fd = open(*path, O_RDONLY);
	if (fd < 0)
	{
		perror("heredoc open");
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("heredoc dup2");
		close(fd);
		return (1);
	}
	close(fd);
	unlink(*path);
	free(*path);
	*path = NULL;
	return (0);
}

int	ft_heredoc(t_central *central, char *del, int doc_type)
{
	int		fd;
	char	*line;

	if (g_signal == 130)
		return (-1);
	fd = doc_prep(central, del, central->curr_cmd_idx, central->curr_hdc_idx);
	if (fd < 0)
		return (-1);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line || ft_strcmp(line, del) == 0
			|| (line[ft_strlen(line) - 1] == '\n'
				&& ft_strncmp(line, del, ft_strlen(del)) == 0
				&& (int)ft_strlen(line) - 1 == (int)ft_strlen(del)))
			break ;
		if (g_signal == 130)
			return (clean_doc(line), 130);
		treat_rl_doc(central, line, doc_type, fd);
		clean_doc(line);
	}
	if (g_signal != 130 && !line)
		return (bad_doc(del), 0);
	return (clean_doc(line), close(fd), 0);
}
