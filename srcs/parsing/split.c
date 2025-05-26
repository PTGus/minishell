/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:08:51 by david-fe          #+#    #+#             */
/*   Updated: 2025/05/26 13:45:00 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Splits user input by pipes to parse commands separately
 * checks for pipes on the ends, error if found
 * allocs, assigns w/ handle_split if pipes are found, and null-terminates
 * @param prompt Full input from readline
 * @return split Array of strings of different commands
 */
char	**ft_split_pipes(char *prompt, t_central *central)
{
	char	**split;
	int		pipe_num;

	if (prompt[0] == '|' || prompt[ft_strlen(prompt) - 1] == '|')
		return (NULL);
	pipe_num = ft_pipe_count(prompt);
	central->matrix_len = 1 + pipe_num;
	split = malloc((pipe_num + 2) * sizeof(char *));
	if (!split)
		return (NULL);
	if (pipe_num == 0)
		split[0] = ft_strdup(prompt);
	else
		ft_handle_split(prompt, split);
	split[pipe_num + 1] = NULL;
	return (split);
}

/**
 * @brief Counts number of pipes for allocation in split_pipes
 * @param prompt Full input from readline
 * @return pipe_num Number of unquoted pipes found
 */
int	ft_pipe_count(char *prompt)
{
	int	i;
	int	pipe_num;

	i = 0;
	pipe_num = 0;
	while (prompt[i])
	{
		if (prompt[i] == '|' && ft_is_quoted(prompt, i) == 0)
			pipe_num++;
		i++;
	}
	return (pipe_num);
}

/**
 * @brief Handles assignment of each string, pipe-pipe or pipe-end
 * @param prompt Full input from readline
 * @param split Allocation for array of strings to return
 * @return split Fully assigned array
 */
char	**ft_handle_split(char *prompt, char **split)
{
	int		i;
	int		j;
	int		str_num;

	i = 0;
	j = 0;
	str_num = 0;
	while (prompt && prompt[i])
	{
		if (prompt[i] == '|' && ft_is_quoted(prompt, i) == 0)
		{
			split[str_num++] = ft_substr(prompt, j, (i - j));
			j = i + 1;
		}
		else if (prompt[i + 1] == '\0' && ft_is_quoted(prompt, i) == 0)
		{
			split[str_num++] = ft_substr(prompt, j, (i - j + 1));
			j = i + 1;
		}
		i++;
	}
	return (split);
}

/**
 * @brief Prints an array of strings for debugging
 * @param str_arr Array of strings to print
 */
void	ft_print_arr(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr && str_arr[i])
	{
		printf("%d: '%s'\n", i, str_arr[i]);
		i++;
	}
}
