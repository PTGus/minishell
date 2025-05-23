/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:07:30 by david-fe          #+#    #+#             */
/*   Updated: 2025/05/22 14:12:55 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_list_array(t_input **array)
{
	int		i;
	t_input	*temp;

	i = -1;
	while (array[++i])
	{
		temp =  array[i];
		while (temp)
		{
			printf("l%i:'%s'\n", temp->index, temp->value);
			temp = temp->next;
		}
		printf("\n");
	}
}

int	ft_assign_list(t_central *central, int i, int l)
{
	int		j;
	int		k;
	int		index;
	t_input *current;
	char	*str;

	j = -1;
	k = 0;
	index = 0;
	str = NULL;
	current = NULL;
	while (central->pipe_matrix[i][++j])
		if (central->pipe_matrix[i][j + 1] == ' '
				|| central->pipe_matrix[i][j + 1] == '\0')
		{
			str = ft_substr(central->pipe_matrix[i], k, (j - k + 1));
			current = ft_input_new(str, index);
			if (!str || !current)
				return (1);
			ft_input_add_back(&central->cmd[l], current);
			k = j + 2;
			j++;
			index++;
		}
	return(0);
}

int	ft_make_list(t_central *central)
{
	int		i;
	int		l;

	central->cmd = malloc((central->matrix_len + 1) * sizeof(t_input*));
	if (!central->cmd)
		return (1);
	i = -1;
	l = 0;
	while (central->pipe_matrix && central->pipe_matrix[++i])
	{
		ft_iter_list(central, i, l);
		l++;
	}
	central->cmd[l] = NULL;
	ft_print_list_array(central->cmd);  //DEL
	ft_free_split(central->pipe_matrix);
	return (0);
}

//	ft_tokenizer(central);

