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

int	ft_odd_quotes(char *prompt)
{
	int	i;
	int singles_num;
	int doubles_num;

	i = 0;
	singles_num = 0;
	doubles_num = 0;
	while (prompt[i])
	{
		if(prompt[i] == '\"')
			doubles_num++;
		else if(prompt[i] == '\'')
			singles_num++;
		i++;
	}
	if (doubles_num % 2 == 1 || singles_num % 2 == 1)
		return (1);
	else
		return(0);
}

char	**ft_split_pipes(char *prompt, t_input input)

void	ft_tokenize(char *prompt)
{
	(void)prompt;
	return ;
}

void	ft_error()
{
	printf("PANTS ARE SHITTED");
	exit(1);
}

void	ft_parse(char *prompt)
{
	t_input	input;

	if(!prompt)
		return ;
	if (ft_odd_quotes(prompt) != 0)
		ft_error();
	if (ft_split_pipes(prompt, &input) == NULL)
		ft_error();
	/*
	prompt = ft_spaced_prompt(prompt);
	ft_tokenize(prompt);
	*/
}
