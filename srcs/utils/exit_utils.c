/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:12:58 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/23 13:08:12 by gumendes         ###   ########.fr       */
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

int	is_under_min(char *val)
{
	char	*min;
	int		len;

	min = "-9223372036854775808";
	len = ft_strlen(val);
	if (len > 20)
		return (1);
	if (len < 20)
		return (0);
	if (ft_strcmp(val, min) > 0)
		return (1);
	return (0);
}

int	is_over_max(char *val)
{
	char	*max;
	int		len;

	if (val[0] == '+')
		val++;
	max = "9223372036854775807";
	len = ft_strlen(val);
	if (len > 19)
		return (1);
	if (len < 19)
		return (0);
	if (ft_strcmp(val, max) > 0)
		return (1);
	return (0);
}
