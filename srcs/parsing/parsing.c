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

void	ft_error(char *message)
{
	printf("%s ERROR! (no exit)\n", message);
}
	//exit(0);

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

/**
 * @brief Central parsing function - inits, checks for open quotes
 * splits by pipes for further parsing, normalizes spacing, 
 * tranforms input into list of tokens
 * @param prompt Full input from readline
 * @param central Struct with pointers to all relevant structs/data
 */
int	ft_parse(char *prompt, t_central *central)
{
	if (prompt[0] == 'x')
		exit(0);
	ft_init_parse(central);
	if (!prompt)
		return (0);
	if (ft_is_quoted(prompt, -1) != 0)
		ft_error("quotes");
	central->pipe_matrix = ft_split_pipes(prompt, central);
	if (central->pipe_matrix == NULL)
		ft_error("pipes");
	if (ft_remove_extra_spaces(central) != 0)
		ft_error("spacing");
	if (ft_space_redirects(central) != 0)
		ft_error("redirect");
	ft_print_arr(central->pipe_matrix);
	printf("\n");
	ft_tokenizer(central);
	ft_expander(central);
	printf("\nEOP\n");
	return (0);
}
