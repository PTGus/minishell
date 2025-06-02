/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:04:40 by gumendes          #+#    #+#             */
/*   Updated: 2025/06/02 15:42:42 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// temporary function to be deleted used only in testing
char	**strip_redirs(char **tok)
{
	int		i;
	int		j;
	int		count;
	char	**out;

	i = 0;
	while (tok[i])
		i++;
	count = i;
	out = ft_calloc(count + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (tok[i])
	{
		if (!ft_strcmp(tok[i], "<") || !ft_strcmp(tok[i], ">")
			|| !ft_strcmp(tok[i], ">>") || !ft_strcmp(tok[i], "<<"))
		{
			if (tok[i + 1])     /* skip operator + filename (if present) */
				i += 2;
			else
				i += 1;         /* malformed: operator at end */
		}
		else
			out[j++] = ft_strdup(tok[i++]);
	}
	out[j] = NULL;
	return (out);
}

void	has_shell_operator(t_central *central, char **split)
{
	char	**tmp;
	if (to_pipe(central, split) == 0)
		return ;
	else
	{
		tmp = strip_redirs(split);
		has_to_redirect(central, split);
		do_cmd(central, tmp);
		ft_freesplit(tmp);
	}
	delete_doc();
}

/**
 * @brief Compares 2 strings to check whether they are the same or not.
 * @return Returns 0 when the strings are equal, < 0 when the s1
 *  is of lower ascii value and > 0 when s1 is of higher ascii value.
 */
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
