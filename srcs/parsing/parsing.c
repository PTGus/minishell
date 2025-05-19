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

/**
 * @brief Returns quoted status of an element 
 * 0 = unquoted, 1 = inside '', 2 = inside ""
 * @param prompt Full input from readline
 * @param end_pos Last element to be checked
 * if end_pos -1 examines whole string
 */
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

/**
 * @brief Initializes all parse related elements in central
 * @param Central struct
 */
void	ft_init_parse(t_central *central)
{
	central->command_list = NULL;
	central->pipe_matrix = NULL;
	central->matrix_len = 0;
}

/**
 * @brief Central parsing function - inits, checks for open quotes
 * splits by pipes for further parsing, normalizes spacing, 
 * tranforms input into list of tokens
 * @param prompt Full input from readline
 * @param central Struct with pointers to all relevant structs/data
 */
int	ft_parse(char *prompt, t_central *central)
{
	ft_init_parse(central);
	if (!prompt)
		return (0);
	if (ft_is_quoted(prompt, -1) != 0)
		ft_error("quotes");
	central->pipe_matrix = ft_split_pipes(prompt, central);
	if (central->pipe_matrix == NULL)
		ft_error("pipes");
	ft_print_arr(central->pipe_matrix);
	if (ft_remove_extra_spaces(central) != 0)
		ft_error("spacing");
	printf("spaced:\n");
	ft_print_arr(central->pipe_matrix);
	//ft_free_split(central->pipe_matrix);
	return (0);
}
