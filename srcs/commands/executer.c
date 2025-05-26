/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:48:09 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/26 15:29:16 by gumendes         ###   ########.fr       */
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

	path = central->dupenv;
	while (ft_strcmp(path->var, "PATH") != 0 && path != NULL)
		path = path->next;
	if (!path)
	{
		central->exit_val = 127;
		return (not_dir(split[0]), 1);
	}
	else
		exec = pather(path, split[0]);
	if (!exec)
	{
		comm_not_foud(split[0]);
		central->exit_val = 127;
		return (free(exec), 1);
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
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("pid");
		exit (1);
	}
	if (pid == 0)
	{
		envp = get_exec_env(&central->dupenv);
		execve(exec, split, envp);
		perror("execve");
		clean_all(central);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(-1, &status, 0);
		central->exit_val = status;
	}
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
