/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_docs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:04:55 by david-fe          #+#    #+#             */
/*   Updated: 2025/07/03 14:50:10 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parsing.h"

/**
 * @brief	Checks if current node val at i pos is $, has a value after
 * and is not inside '', and not immediately followed by a "
 * @return	0 if correct, 1 on malloc error
*/
char	*ft_check_expand_doc(t_central *central, char *str)
{
	int		i;
	char	*new_str;
	char	*temp;

	temp = str;
	new_str = NULL;
	i = 0;
	while (temp[i])
	{
		if (temp[i] == '$' && temp[i + 1] && ft_is_quoted(temp, i) != 1
			&& (temp[i + 1] != '\"'))
		{
			new_str = ft_execute_expand_doc(central, &temp, i,
					ft_get_expand_doc(temp, i + 1));
			if (!new_str)
				return (NULL);
			i = 0;
		}
		else
			i++;
	}
	if (!new_str)
		return (ft_strdup(temp));
	else
		return (new_str);
}

/**
 * @brief Obtains the position at which the current expansion ends.
 * @param first 1 = first position checked, important for numbers and
 * special characters.
 * @return Position of the last element of string to expand.
*/
int	ft_get_expand_doc(char *str, int j)
{
	int	first;

	first = 1;
	while (str[j])
	{
		if ((str[j] == '?' || str[j] == '$') && first == 1)
			return (j);
		else if (ft_isdigit(str[j]) == 1 && first == 1)
			return (j);
		else if (ft_isalpha(str[j]) == 1 || str[j] == '_'
			|| (ft_isdigit(str[j]) == 1 && first == 0))
			first = 0;
		else
			return (j - 1);
		j++;
	}
	return (j - 1);
}

/**
 * @brief	Iterates and reassings pre-expand, expand (which changes), and 
 * post-expand
 * @param	str - String to copy pre and post from
 * @param	new_str - Previously alloc'ed to hold result
 * @param	expand - Result of expansion to copy into new_str
 * @param	vals - Array with ints: start(0) and end(1) pos for 
 * expand in str, and new len(2)
 * @return
*/
char	*ft_assign_expand_doc(char **str, int *vals,
	char *new_str, char *expand)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (j < vals[0])
		new_str[i++] = (*str)[j++];
	j = 0;
	while (expand[j])
		new_str[i++] = expand[j++];
	j = vals[1] + 1;
	while ((*str)[j])
		new_str[i++] = (*str)[j++];
	temp = *str;
	*str = new_str;
	return (new_str);
}

/**
 * @brief	Obtains and sets up values for doing expansions in assign_expand
 * @param	null_expand - Flag for expand=NULL, to avoid segfault in free
 *  because getenv can't be freed, but empty substr must be
 * @param	vals - Array with ints: start(0) and end(1) pos for
 * expand in str, and new len(2)
 * @return	0 if correct, 1 on malloc error
*/
char	*ft_execute_expand_doc(t_central *central,
		char **str, int start, int end)
{
	char	*temp;
	char	*expand;
	char	*new_str;
	int		vals[3];

	temp = ft_substr(*str, start + 1, end - start);
	if (!temp)
		return (NULL);
	expand = ft_get_dupenv_val(central, temp);
	if (!expand)
		expand = ft_strdup("");
	vals[0] = start;
	vals[1] = end;
	vals[2] = start + ft_strlen(expand) + ft_strlen(*str + end + 1);
	new_str = ft_calloc((vals[2] + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	new_str = ft_assign_expand_doc(str, vals, new_str, expand);
	ft_free_strings(temp, expand);
	return (new_str);
}
/*
void	ft_delete_empty_expands(t_input **array)
{
	int		i;
	t_input *current;
	t_input	*temp;
	t_input *first;

	i = -1;
	while (array[++i])
	{
		first = array[i];
		current = first;
		while (current)
		{
			if (current->token == DELETE)
			{

				temp = ft_input_delete_node(current);
				current = temp;
			}
			else 
				current = current->next;
		}
	}
}*/
