/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:12:19 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/07 16:33:25 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Transforms into a string, the dupenv node's variable and value.
 * @param dupenv The node with the needed information.
 * @return The created string.
 */
char	*get_line(t_envp *dupenv)
{
	char	*str;
	char	*tmp;

	str = ft_strdup("");
	tmp = str;
	str = ft_strjoin(tmp, dupenv->var);
	free(tmp);
	tmp = str;
	str = ft_strjoin(tmp, "=");
	free(tmp);
	tmp = str;
	str = ft_strjoin(tmp, dupenv->value);
	free(tmp);
	return (str);
}

/**
 * @brief Gets all the necessary variables from the
 *  dupenv list to ensure that execve is successful.
 * @param dupenv The main list and head that contains a dupliate of envp.
 * @return A NULL terminated array of arrays with the desired variables.
 */
char	**get_exec_env(t_envp **dupenv)
{
	t_envp	*tmp;
	int		i;
	char	**vars;

	tmp = *dupenv;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	vars = ft_calloc(i + 1, sizeof(char *));
	tmp = *dupenv;
	i = 0;
	while (tmp)
	{
		vars[i] = get_line(tmp);
		tmp = tmp->next;
		i++;
	}
	vars[i] = NULL;
	return (vars);
}
