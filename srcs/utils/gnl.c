/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:03:41 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/10 12:08:00 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free(char **ptr);
char	*set_line(char *str);
char	*fill_line(int fd, char *nxt, char *buf);

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*nxt;

	if (fd < 0)
		return (NULL);
	buf = malloc((10 + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	line = fill_line(fd, nxt, buf);
	ft_free(&buf);
	if (!line)
	{
		ft_free(&nxt);
		ft_free(&line);
		return (NULL);
	}
	nxt = set_line(line);
	return (line);
}

void	ft_free(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	*set_line(char *str)
{
	char	*nxt;
	size_t	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	nxt = ft_substr(str, i + 1, ft_strlen(str) - i);
	if (!nxt || nxt[0] == '\0')
	{
		ft_free(&nxt);
		return (NULL);
	}
	str[i + 1] = 0;
	return (nxt);
}

char	*handle_read_error(int check, char **nxt)
{
	if (check == 0)
		return (*nxt);
	ft_free(nxt);
	return (NULL);
}

char	*fill_line(int fd, char *nxt, char *buf)
{
	char		*str;
	int			check;

	check = 1;
	while (check > 0)
	{
		check = read(fd, buf, 10);
		if (check <= 0)
			return (handle_read_error(check, &nxt));
		buf[check] = '\0';
		if (!nxt)
			nxt = ft_strdup("");
		str = nxt;
		nxt = ft_strjoin(str, buf);
		ft_free(&str);
		if (!nxt)
			return (NULL);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (nxt);
}
