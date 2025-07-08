/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:46:42 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/08 16:10:54 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	bad_export(char *str)
{
	int		err_len;
	char	*err_msg;
	char	*tmp;

	err_msg = "bash: export: \'";
	err_msg = ft_strjoin(err_msg, str);
	tmp = err_msg;
	err_msg = ft_strjoin(tmp, "': not a valid identifier\n");
	free(tmp);
	err_len = ft_strlen(err_msg);
	write(2, err_msg, err_len);
	free(err_msg);
}

void	bad_doc(char *str)
{
	int		err_len;
	char	*err_msg;
	char	*tmp;

	err_msg = "bash: warning: here-document at line 1 delimited";
	err_msg = ft_strjoin(err_msg, "by end-of-file (wanted `");
	tmp = err_msg;
	err_msg = ft_strjoin(tmp, str);
	free(tmp);
	tmp = err_msg;
	err_msg = ft_strjoin(tmp, "')\n");
	free(tmp);
	err_len = ft_strlen(err_msg);
	write(2, err_msg, err_len);
	free(err_msg);
}

void	no_perms(char *str)
{
	int		err_len;
	char	*err_msg;
	char	*tmp;

	err_msg = ft_strjoin("bash: ", str);
	tmp = err_msg;
	err_msg = ft_strjoin(tmp, ": Permission denied\n");
	free(tmp);
	err_len = ft_strlen(err_msg);
	write(2, err_msg, err_len);
	free(err_msg);
}

/**
 * @brief A error message for when a command is not found.
 */
void	comm_not_found(char *str)
{
	int		err_len;
	char	*err_msg;

	err_msg = ft_strjoin(str, ": command not found\n");
	err_len = ft_strlen(err_msg);
	write(2, err_msg, err_len);
	free(err_msg);
}

/**
 * @brief A error message for when the specified
 *  file/folder is not found.
 */
void	not_cd_dir(char *str)
{
	int		err_len;
	char	*err_msg;
	char	*tmp;

	err_msg = "bash: cd: ";
	err_msg = ft_strjoin(err_msg, str);
	tmp = err_msg;
	err_msg = ft_strjoin(tmp, ": No such file or directory\n");
	free(tmp);
	err_len = ft_strlen(err_msg);
	write(2, err_msg, err_len);
	free(err_msg);
}
