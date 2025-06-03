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

int ft_get_expand_end(char *str, int j) //TO_DO -> $ ONLY prints in "" if it's the only element, otherwise expands to valid or nothing
{
	int first;

	first = 1;
	while (str[j])
	{
		if ((str[j] == '?' || str[j] == '$') && first == 1)
			return (printf("return spec %i for %c\n", j, str[j]), j);
		else if (ft_isdigit(str[j]) == 1 && first == 1)
			return (printf("return num %i for %c\n", j, str[j]), j);
		else if (ft_isalpha(str[j]) == 1 || str[j] == '_'
			|| (ft_isdigit(str[j]) == 1 && first == 0))
			first = 0;
		else
			return (printf("return misc %i for %c\n", j - 1, str[j - 1]), j - 1);
		j++;
	}
	return (printf("return end %i for %c\n", j - 1, str[j - 1]), j - 1);
}

void	ft_assign_expand(char *str, int *vals, char *new_str, char *expand)
{
	int	i;
	int	j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (i < vals[2])
	{
		if (i <= vals[0])
			new_str[i] = str[j++];
		else if (i > vals[0] && i <= vals[1])
		{
			new_str[i] = expand[k++];
			if (i == vals[1])
				j = j + (vals[1] - vals[0] + 1) + 1;			
		}
		else if (i > vals[1])
			new_str[i] = str[j++];
		printf("%i:'%s'\n", i, new_str);
		i++;
	}
	printf("'%s' expanded with '%s':\n'%s'\n", str, expand, new_str);
}

int	ft_execute_expand(char *str, int start, int end)
{
	char	*temp;
	char	*expand;
	char	*new_str;
	int		vals[3];

	temp = ft_substr(str, start + 1, end - start + 1);
	if (!temp)
		return (1);
	expand = getenv(temp);
	vals[0] = start;
	vals[1] = end;
	vals[2] = ft_strlen(str) - (ft_strlen(temp) + 1) + ft_strlen(expand);
	new_str = ft_calloc((vals[2] + 1), sizeof(char));
	if (!new_str)
		return (1);
	ft_assign_expand(str, vals, new_str, expand);
	printf("expand %s\nresult %s", temp, expand);
	return (0);
}

//iter through list
//if a $ is found unquoted use getenv to substitute
//remeber double quotes vs single
void ft_check_expand(t_input *node)
{
	int i;
	int j;

	i = 0;
	while (node->value[i])
	{
		j = 0;
		printf("i is %i\n", i);
		if (node->value[i] == '$' && node->value[i + 1]
			&& ft_is_quoted(node->value, i) != 1)
		{
			printf("found $-> %s @[%i]\n", node->value, i);
			j = ft_get_expand_end(node->value, i + 1);
			if (ft_execute_expand(node->value, i, j) == 0)
				return ;
			//NEED TO DO i = 0 after expand
			//printf("j is %i\n", j);
		//	i = j + 1;
		//	printf("i becomes %i\n", i);
		}
		else 
			i++;
	}
}

int	ft_expander(t_central *central)
{
	int		i;
	t_input *current;
	t_input *next;

	i = -1;
	while (central->cmd[++i])
	{
		current = central->cmd[i];
		while (current)
		{
			next = current->next;
			if (current && current->token == 0)
				ft_check_expand(current);
			current = next;
		}

	}
	return (0);
}
