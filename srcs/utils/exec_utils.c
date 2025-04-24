/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:12:19 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/24 17:20:37 by gumendes         ###   ########.fr       */
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
	char	**vars;

	vars = ft_calloc(6, sizeof(char *));
	tmp = *dupenv;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, "PATH") == 0 && vars[0] == NULL)
			vars[0] = get_line(tmp);
		else if (ft_strcmp(tmp->var, "HOME") == 0 && vars[1] == NULL)
			vars[1] = get_line(tmp);
		else if (ft_strcmp(tmp->var, "USER") == 0 && vars[2] == NULL)
			vars[2] = get_line(tmp);
		else if (ft_strcmp(tmp->var, "SHELL") == 0 && vars[3] == NULL)
			vars[3] = get_line(tmp);
		else if (ft_strcmp(tmp->var, "TERM") == 0 && vars[4] == NULL)
			vars[4] = get_line(tmp);
		tmp = tmp->next;
	}
	vars[5] = NULL;
	return (vars);
}
