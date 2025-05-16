/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:27:01 by david-fe          #+#    #+#             */
/*   Updated: 2025/05/06 12:18:38 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_quoted(char *prompt, int end_pos)
{
	int	i;
	int	quote_flag;

	i = -1;
	quote_flag = 0;
	if (end_pos == -1)
		end_pos = ft_strlen(prompt) - 1;
	while (prompt[++i] && i <= end_pos)
	{
		if (prompt[i] == '\'' && quote_flag == 0)
			quote_flag = 1;
		else if (prompt[i] == '\'' && quote_flag == 1)
			quote_flag = 0;
		else if (prompt[i] == '\"' && quote_flag == 0)
			quote_flag = 2;
		else if (prompt[i] == '\"' && quote_flag == 2)
			quote_flag = 0;
	}
	return (quote_flag);
}

void	ft_error(char *message)
{
	printf("%s ERROR! (no exit)\n", message);
}
	//exit(0);

void	ft_tokenize(char *prompt)
{
	(void)prompt;
	return ;
}

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
