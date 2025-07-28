/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:49:16 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/21 17:35:22 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	no_redir_err(void)
{
	int	err_len;

	err_len = ft_strlen("bash: syntax error near unexpected token `newline'\n");
	write(2, "bash: syntax error near unexpected token `newline'\n", err_len);
}

void	no_oldpwd(void)
{
	int	err_len;

	err_len = ft_strlen("bash: cd: OLDPWD not set\n");
	write(2, "bash: cd: OLDPWD not set\n", err_len);
}

void	no_file_dir(char *str)
{
	int		err_len;
	char	*err_msg;
	char	*tmp;

	err_msg = "bash: ";
	err_msg = ft_strjoin(err_msg, str);
	tmp = err_msg;
	err_msg = ft_strjoin(tmp, ": No such file or directory\n");
	free(tmp);
	err_len = ft_strlen(err_msg);
	write(2, err_msg, err_len);
	free(err_msg);
}
