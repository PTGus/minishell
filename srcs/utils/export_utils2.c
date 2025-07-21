/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:59:49 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/21 15:21:37 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validity_check(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0)
			break ;
		i++;
	}
	if (str[i] == '\0')
		return (0);
	if (str[i] == '+' && str[i + 1] == '=')
		return (0);
	if (str[i] == '=')
		return (0);
	return (1);
}
