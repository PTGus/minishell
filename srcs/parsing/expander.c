/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:12:17 by david-fe          #+#    #+#             */
/*   Updated: 2025/05/26 15:18:27 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief	Obtains the position at which the current expansion ends
 * @param	first -  1= first position checked, important for numbers and
 * special characters
 * @return	Position of the last element of string to expand
*/
int	ft_get_expand_end(char *str, int j)
{
	int	first;

	first = 1;
	while (str[j])
	{
		if ((str[j] == '?' || str[j] == '$') && first == 1)
			return (printf("return spec %i for %c\n", j, str[j]), j);
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
 * expand in str, * and new len(2)
 * @return
*/ 
void	ft_assign_expand(char **str, int *vals, char *new_str, char *expand)
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
	free(temp);
}

/**
 * @brief	
 * @param
 * @return
*/ 
char	*ft_get_dupenv_val(char *str) //SWAP GETENV WITH DUPENV
{
	if (ft_strncmp(str, "$", 1) == 0)
		return ("PID");
	else if (ft_strncmp(str, "?", 1) == 0)
		return ("TEMP_EXIT");
	else
		return (getenv(str));
}

/**
 * @brief	
 * @param
 * @return
*/ 
int	ft_execute_expand(char **str, int start, int end)
{
	char	*temp;
	char	*expand;
	char	*new_str;
	int		vals[3];
	int		null_exp;

	null_exp = 1;
	temp = ft_substr(*str, start + 1, end - start);
	if (!temp)
		return (1);
	expand = ft_get_dupenv_val(temp);
	if (expand)
		null_exp = 0;
	else
		expand = ft_strdup("");
	vals[0] = start;
	vals[1] = end;
	vals[2] = start + ft_strlen(expand) + ft_strlen(*str + end + 1);
	new_str = ft_calloc((vals[2] + 1), sizeof(char));
	if (!new_str)
		return (1);
	ft_assign_expand(str, vals, new_str, expand);
	ft_free_strings(temp, expand, null_exp);
	return (0);
}

/**
 * @brief	
 * @param
 * @return
*/ 
void	ft_check_expand(t_input *node)
{
	int	i;
	int	j;

	i = 0;
	while (node->value[i])
	{
		j = 0;
		if (node->value[i] == '$' && node->value[i + 1]
			&& ft_is_quoted(node->value, i) != 1
			&& (node->value[i + 1] != '\"'))
		{
			printf("found $-> %s @[%i]\n", node->value, i);
			j = ft_get_expand_end(node->value, i + 1);
			if (ft_execute_expand(&node->value, i, j) == 1)
				return ;
			i = 0;
			printf("node val is: '%s'\n", node->value);
		}
		else
			i++;
	}
}

int	ft_expander(t_central *central)
{
	int		i;
	t_input	*current;
	t_input	*next;

	i = -1;
	while (central->cmd[++i])
	{
		current = central->cmd[i];
		while (current)
		{
			if (current && current->token == 0)
			{
				ft_check_expand(current);
				ft_is_node_spaced(current);
			}
			next = current->next;
			current = next;
		}
	}
	ft_print_list_array(central->cmd);
	return (0);
}
