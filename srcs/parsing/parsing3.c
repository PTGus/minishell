/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:10:09 by david-fe          #+#    #+#             */
/*   Updated: 2025/05/15 17:10:53 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_remove_extra_spaces(char **split)
{
	int		i;
	int		j;
	int		flag;
	char	**new_split;

	i = -1;
	j = -1;
	flag = 0;
	new_split = malloc(sizeof(char *));
	while (split && split[++i])
		new_split[i] = malloc((ft_spaced_len(split[i]) + 1) * sizeof(char *));
	i = -1;
	while (split && split[++i])
	{
		while (split[i][++j])
		{
			printf("placeholder");
		}
	}
	new_split = NULL;
	return (new_split);
}
// NEED TO KNOW SPLIT LEN for new_split malloc

int	ft_parse(char *prompt)
{
	char	**pipe_split;

	if (!prompt)
		return (0);
	if (ft_is_quoted(prompt, -1) != 0)
		ft_error("quotes");
	pipe_split = ft_split_pipes(prompt);
	if (pipe_split == NULL)
		ft_error("pipes");
	ft_print_arr(pipe_split);
	ft_remove_extra_spaces(pipe_split);
	ft_free_split(pipe_split);
	return (0);
}
