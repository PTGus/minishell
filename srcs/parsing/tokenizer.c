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

//TO-DO make print utils file to free space for 1 function, rewrite assign list
int	ft_assign_list(t_central *central, int i, int l)
{
	int		j;
	int		k;
	int		index;
	t_input	*current;
	char	*str;

	j = 0;
	k = 0;
	index = 0;
	while (central->pipe_matrix[i] && central->pipe_matrix[i][j]) //am i trying to access one address after max len? is it \0?
	{
		if ((central->pipe_matrix[i][j + 1] && central->pipe_matrix[i][j + 1] == ' '
			&& ft_is_quoted(central->pipe_matrix[i], j + 1) == 0)
			|| central->pipe_matrix[i][j + 1] == '\0')
		{
			str = ft_substr(central->pipe_matrix[i], k, (j - k + 1));
			current = ft_input_new(str, index++);
			if (!str || !current)
				return (ft_free_list_err(central, str, current), 1);
			ft_input_add_back(&central->cmd[l], current);
			k = 2 + j++;
		}
		if (central->pipe_matrix[i][j] != '\0')
			j++;
	}
	return (0);
}

int	ft_make_list(t_central *central)
{
	int		i;
	int		l;

	central->cmd = malloc((central->matrix_len + 1) * sizeof(t_input *));
	printf("matrix_len %i\n", central->matrix_len);
	if (!central->cmd)
		return (1);
	i = -1;
	l = 0;
	while (l < central->matrix_len)
		central->cmd[l++] = NULL;
	l = 0;
	while (central->pipe_matrix && central->pipe_matrix[++i])
	{
		if (ft_assign_list(central, i, l++) != 0)
			return (1);
	}
	central->cmd[l] = NULL;
	ft_free_split(central->pipe_matrix);
	return (0);
}

int	ft_is_delimiter_quoted(t_input *current)
{
	int		i;
	char	*next_val;

	i = -1;
	next_val = current->next->value;
	while (next_val && next_val[++i])
		if (next_val[i] == '\"' || next_val[i] == '\'')
			return (1);
	return(0);
}

void	ft_assign_token(t_input *node)
{
	if (node->token != -1 || node->value == NULL)
		return ;
	if (ft_strcmp("<", node->value) == 0)
		node->token = REDIR_IN;
	else if (ft_strcmp(">", node->value) == 0)
		node->token = REDIR_OUT;
	else if (ft_strcmp(">>", node->value) == 0)
		node->token = APPEND_OUT;
	else if (ft_strcmp("<<", node->value) == 0)
	{
		if (ft_is_delimiter_quoted(node) == 0)
			node->token = HERE_DOC;
		else
			node->token = HERE_DOC_Q;
	}
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
	//ft_free_list_err(central, NULL, NULL);
	return (0);
}
