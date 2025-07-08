/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:27:01 by david-fe          #+#    #+#             */
/*   Updated: 2025/07/08 11:40:53 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Central parsing function - inits, checks for open quotes
 * splits by pipes for further parsing, normalizes spacing,
 *  tranforms input into list of tokens
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
	ft_remove_extra_spaces(central);
	ft_space_redirects(central);
	ft_tokenizer(central);
	ft_expander(central);
	ft_quote_eraser(central);
	return (0);
}

/**
 * @brief Initializes all parse related elements in central
 * @param Central struct
 */
void	ft_init_parse(t_central *central)
{
	central->cmd = NULL;
	central->pipe_matrix = NULL;
	central->matrix_len = 0;
}

void	ft_error(char *message)
{
	printf("%s ERROR! (no exit)\n", message);
}
