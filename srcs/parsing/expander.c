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

int ft_get_expand_end(char *str, int j, int qt) //TO_DO -> $ ONLY prints in "" if it's the only element, otherwise expands to valid or nothing
{
	int first;

	(void)qt;//DEL?
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

int	ft_execute_expand(char *str, int i, int j)
{
	char *temp;
	char *expand;

	temp = ft_substr(str, i + 1, j - i + 1);
	if (!temp)
		return (1);
	expand = getenv(temp);
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
			j = ft_get_expand_end(node->value, i + 1, ft_is_quoted(node->value, i));
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
