/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:08:51 by david-fe          #+#    #+#             */
/*   Updated: 2025/05/15 17:09:40 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(char *message)
{
	printf("%s ERROR! (no exit)\n", message);
}
	//exit(0);

void	ft_print_arr(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr && str_arr[i])
	{
		printf("%d: %s\n", i, str_arr[i]);
		i++;
	}
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
		while (split[i])
			free(split[i++]);
	if (split)
		free(split);
}

int	ft_is_space(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int	ft_spaced_len(char *command)
{
	int	j;
	int	flag;
	int	len;

	j = -1;
	len = 0;
	flag = 0;
	while (command && command[++j])
	{
		if (!ft_is_space(command[j]))
		{
			len++;
			flag = 1;
		}
		else if (flag == 1 && ft_is_space(command[j]) == 1)
			flag = 0;
	}
	return (len);
}
