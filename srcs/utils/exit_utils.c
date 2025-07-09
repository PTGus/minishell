/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:12:58 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/09 14:14:33 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_all_signs(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '-' && str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}
