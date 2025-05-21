/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_spacing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:30:00 by david-fe          #+#    #+#             */
/*   Updated: 2025/05/21 13:39:33 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_realloc_redir_str(char *str, int to_space)
{
	char *new_str;
	int	new_len;
	int j;
	int k;

	j = 0;
	k = -1;
	new_len = ft_strlen(str) + to_space;
	new_str = malloc((new_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	while (str[++k])
	{
		if (ft_count_unspaced_redirects(str, k, 0) == 1)
		{
			new_str[j] = str[k];
			new_str[++j] = ' ';
		}
		else
			new_str[j] = str[k];
		j++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}
//	printf("\nmem: %i\n", new_len);
//	printf("str: %s\n", str);
//	printf("new: %s\n", new_str);

int	ft_count_unspaced_redirects(char *str, int j, int extra_space)
{
	if(str[j + 1])
	{
		if (((ft_strchr("<>", str[j]) && !ft_is_quoted(str, j))
			&& !ft_strchr("< >", str[j + 1])) || (!ft_strchr("< >", str[j])
			&& (ft_strchr("<>", str[j + 1]) && !ft_is_quoted(str, j + 1)))) 
			extra_space++;
	}
	if (extra_space != 0)
		printf("X%i\n", extra_space);
	return (extra_space);
}

int	ft_space_redirects(t_central *central)
{
	int	i;
	int	j;
	int to_space;

	i = -1;
	j = -1;
	while (central->pipe_matrix && central->pipe_matrix[++i])
	{
		to_space = 0;
		while (central->pipe_matrix[i][++j])
		{
			//printf("%i:%c ", j, central->pipe_matrix[i][j]); //DEL
			to_space = 
				ft_count_unspaced_redirects(central->pipe_matrix[i], j, to_space);
		}
		if (to_space > 0)
		{
			printf("[%i]\n", to_space); //DEL
			central->pipe_matrix[i] = 
				ft_realloc_redir_str(central->pipe_matrix[i], to_space);
		}
		printf("\n"); //DEL
		j = -1;
	}
	return (0);
}


