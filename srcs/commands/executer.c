/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:48:09 by gumendes          #+#    #+#             */
/*   Updated: 2025/06/30 17:07:08 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_exec_error(char *cmd);

/**
 * @brief Finds out whether the command exists
 *  or not, if it exists it executes it.
 * @param central A struct that contains pointers to
 *  all the neccessary variables and lists.
 * @param split An array of arrays with the prompt received from read line.
 */
int	commander(t_central *central, t_input *cmd)
{
	t_envp	*path;
	t_input	*tmp_cmd;
	char	*exec;

	tmp_cmd = find_cmd(cmd);
	path = ft_getenv(&central->dupenv, "PATH");
	if (!path)
	{
		not_dir(tmp_cmd->value);
		clean_all(central);
		exit(127);
	}
	else
		exec = pather(path, tmp_cmd->value);
	if (!exec)
	{
		clean_all(central);
		check_exec_error(tmp_cmd->value);
	}
	executer(exec, central, tmp_cmd);
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
void	executer(char *exec, t_central *central, t_input *cmd)
{
	char	**exec_flags;
	char	**envp;

	exec_flags = get_exec_flags(cmd);
	envp = get_exec_env(&central->dupenv);
	execve(exec, exec_flags, envp);
	clean_all(central);
	ft_free_split(envp);
	ft_free_split(exec_flags);
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

static void	check_exec_error(char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Is a directory", 2);
		exit(126);
	}
	else
	{
		comm_not_found(cmd);
		exit(127);
	}
}
