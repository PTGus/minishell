/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:48:09 by gumendes          #+#    #+#             */
/*   Updated: 2025/06/25 14:28:52 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Finds out whether the command exists
 *  or not, if it exists it executes it.
 * @param central A struct that contains pointers to
 *  all the neccessary variables and lists.
 * @param split An array of arrays with the prompt received from read line.
 */
int	commander(t_central *central, char **split)
{
	t_envp	*path;
	char	*exec;

	path = ft_getenv(&central->dupenv, "PATH");
	if (!path)
	{
		not_dir(split[0]);
		clean_all(central);
		exit(127);
	}
	else
		exec = pather(path, split[0]);
	if (!exec)
	{
		comm_not_foud(split[0]);
		free(exec);
		clean_all(central);
		exit(127);
	}
	executer(exec, central, split);
	free(exec);
	return (0);
}

/**
 * @brief Executes a command through execve.
 * @param exec The command to execute.
 * @param split An array of arrays with the prompt received from read line.
 * @param central A struct that contains pointers to
 *  all the neccessary variables and lists.
 */
void	executer(char *exec, t_central *central, char **split)
{
	char	**envp;

	envp = get_exec_env(&central->dupenv);
	execve(exec, split, envp);
	clean_all(central);
	ft_free_split(envp);
	exit(1);
}

/**
 * @brief Iterates through all the "PATH" variable paths in order
 *  to find the one which allows execution of the required command.
 * @param path The node of the dupenv list that holds the PATH variable.
 * @param cmd The command to find.
 * @return In case of the command having been found it returns the path
 *  to executtable (ex.:"/bin/ls"), if not found returns NULL.
 */
char	*pather(t_envp *path, char *cmd)
{
	int		i;
	char	*exec;
	char	**all_paths;
	char	*path_part;

	if (is_relative(cmd) == 0)
		return (ft_strdup(cmd));
	all_paths = ft_split(path->value, ':');
	i = -1;
	while (all_paths[++i])
	{
		path_part = ft_strjoin(all_paths[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_freesplit(all_paths);
			return (exec);
		}
		free(exec);
	}
	ft_freesplit(all_paths);
	return (NULL);
}
