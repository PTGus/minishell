/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:59:49 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/28 13:30:02 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validity_check(char *str)
{
	size_t	i;

	i = 1;
	if (ft_isalnum(str[i]) == 0 && str[0] != '_')
		return (1);
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

void	trunc_export(t_envp *var, char *exportion, int index)
{
	char	*tmp;
	char	*tmp2;
	int		len;

	if (var->value != NULL)
	{
		tmp = ft_strdup(var->value);
		free(var->value);
		len = ft_strlen(exportion) - (index + 1);
		tmp2 = ft_substr(exportion, index + 2, len);
		var->value = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
	}
	else
	{
		var->value = ft_strdup(exportion + index + 2);
		var->visible_env = TRUE;
		var->has_equal = TRUE;
	}
}
