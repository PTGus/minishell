/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:07:30 by david-fe          #+#    #+#             */
/*   Updated: 2025/07/28 13:20:52 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief	Calls functions to transform matrix of command strings into
 * matrix of lists, each node being a space separated element of the str,
 *  and assigns a value to each node based on its type
 * @return	0 on no error, 1 on malloc error of called functions,
 *  2 on assign token error
*/
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
			if (ft_assign_token(temp) == 1)
				return (ft_free_list_err(central, NULL, NULL), 2);
			temp = temp->next;
		}
	}
	return (0);
}
//ft_free_list_err(central, NULL, NULL);

/**
 * @brief	Allocates new array of list and iterates for assigment.
 * @return	0 on no error, 1 on malloc error here or in assign_list.
*/
int	ft_make_list(t_central *central)
{
	int		i;
	int		l;

	central->cmd = malloc((central->matrix_len + 1) * sizeof(t_input *));
	if (!central->cmd)
		return (1);
	i = -1;
	l = 0;
	while (l < central->matrix_len)
		central->cmd[l++] = NULL;
	l = 0;
	while (central->pipe_matrix && central->pipe_matrix[++i])
	{
		if (ft_assign_list(central, i, l++, 0) != 0)
			return (1);
	}
	central->cmd[l] = NULL;
	ft_free_split(central->pipe_matrix);
	return (0);
}

/**
 * @brief	Assigns the list per space-separated element into nodes,
 *  creating and assigning them to the back
 * @return	0 if all correct, 1 on malloc error
*/
int	ft_assign_list(t_central *central, int i, int l, int index)
{
	int		j;
	int		k;
	t_input	*current;
	char	*str;

	j = 0;
	k = 0;
	while (central->pipe_matrix[i] && central->pipe_matrix[i][j])
	{
		if ((central->pipe_matrix[i][j + 1] && central->pipe_matrix[i][j + 1]
			== ' ' && ft_is_quoted(central->pipe_matrix[i], j + 1) == 0)
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

/**
 * @brief	Assings a value to node token, for string or redirect type
*/
int	ft_assign_token(t_input *node)
{
	if (node->token != -1 || node->value == NULL)
		return (1);
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
	return (0);
}

/**
 * @brief	Used to check whether the element after a here_doc is quoted
 * (because this affects expansion if content before delimiter can expand)
 * @return	0 if no quotes, 1 if any quote is found
*/
int	ft_is_delimiter_quoted(t_input *current)
{
	int		i;
	char	*next_val;

	i = -1;
	if (current->next)
	{
		next_val = current->next->value;
		while (next_val && next_val[++i])
			if (next_val[i] == '\"' || next_val[i] == '\'')
				return (1);
	}
	return (0);
}
