/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:48:09 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/07 15:26:10 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	commander(t_central *central, char **split)
{
	t_envp	*path;
	char	*exec;

	path = central->dupenv;
	while (ft_strcmp(path->var, "PATH") != 0 && path != NULL)
		path = path->next;
	if (!path)
		return (printf("bash: %s: No such file or directory\n", split[0]), 1);
	else
		exec = pather(path, split[0]);
	if (!exec)
	{
		printf("bash: %s: command not found\n", exec);
		central->exit_val = 127;
		return (free(exec), 1);
	}
	executer(exec, split, central);
	free(exec);
	return (0);
}

void	executer(char *exec, char **split, t_central *central)
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
		envp = get_exec_env(central->dupenv);
		execve(exec, split, envp);
		perror("execve");
        ft_freesplit(envp);
        exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
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
