/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:49:16 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/09 13:52:16 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	no_oldpwd(void)
{
	int	err_len;

	err_len = ft_strlen("bash: cd: OLDPWD not set\n");
	write(2, "bash: cd: OLDPWD not set\n", err_len);
}
