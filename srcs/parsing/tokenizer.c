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
		temp = array[i];
		while (temp)
		{
			printf("l%i:'%s'(t:%i)\n", temp->index, temp->value, temp->token);
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
	t_input	*current;
	char	*str;

	j = -1;
	k = 0;
	index = 0;
	while (central->pipe_matrix[i][++j])
	{
		if ((central->pipe_matrix[i][j + 1] == ' '
			&& ft_is_quoted(central->pipe_matrix[i], j + 1) != 0)
			|| central->pipe_matrix[i][j + 1] == '\0')
		{
			str = ft_substr(central->pipe_matrix[i], k, (j - k + 1));
			current = ft_input_new(str, index++);
			if (!str || !current)
				return (ft_free_list_err(central, str, current), 1);
			ft_input_add_back(&central->cmd[l], current);
			k = j + 2;
			j++;
		}
	}
	return (0);
}

int	ft_make_list(t_central *central)
{
	int		i;
	int		l;

	central->cmd = malloc((central->matrix_len + 1) * sizeof(t_input *));
	if (!central->cmd)
		return (1);
	i = -1;
	l = 0;
	while (central->pipe_matrix && central->pipe_matrix[++i])
	{
		ft_assign_list(central, i, l);
		l++;
	}
	central->cmd[l] = NULL;
	ft_print_list_array(central->cmd);
	ft_free_split(central->pipe_matrix);
	return (0);
}

void	ft_assign_token(t_input *node)
{
	if (node->token != -1 || node->value == NULL)
		return ;
	if (ft_strcmp("<", node->value) == 0)
		node->token = REDIR_IN;
	else if (ft_strcmp(">", node->value) == 0)
		node->token = REDIR_OUT;
	else if (ft_strcmp("<<", node->value) == 0)
		node->token = HERE_DOC;
	else if (ft_strcmp(">>", node->value) == 0)
		node->token = APPEND_OUT;
	else
		node->token = ARGUMENT;
}

int	ft_tokenizer(t_central *central)
{
	int		i;
	t_input	*temp;

	i = -1;
	if (ft_make_list(central) != 0)
		return (1);
	while (central->cmd[++i])
	{
		temp = central->cmd[i];
		while (temp)
		{
			ft_assign_token(temp);
			temp = temp->next;
		}
	}
	ft_print_list_array(central->cmd);
	ft_free_list_err(central, NULL, NULL);
	return (0);
}
