/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:52:08 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/28 10:46:39 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cmd_remainder_cleanup(char **envp,
	char **exec_flags, t_central *central)
{
	ft_free_split(envp);
	ft_free_split(exec_flags);
	clean_all(central);
}

static int	do_received_cmd(t_central *central, t_input *cmd)
{
	char	*exec;
	char	*tmp;
	char	**exec_flags;
	char	**envp;

	exec = NULL;
	if (is_relative(cmd->value) == 0)
	{
		tmp = getcwd(NULL, 0);
		exec = ft_strjoin(tmp, cmd->value + 1);
		free(tmp);
	}
	if (access(cmd->value, F_OK) == 0 && access(cmd->value, X_OK) == 0)
	{
		exec_flags = get_exec_flags(cmd);
		envp = get_exec_env(&central->dupenv);
		if (exec)
			execve(exec, exec_flags, envp);
		else
			execve(cmd->value, exec_flags, envp);
		cmd_remainder_cleanup(envp, exec_flags, central);
		exit(1);
	}
	else
		return (127);
}

static int	do_local(t_central *central, t_input *cmd)
{
	char	*tmp;
	char	*exec;
	char	**exec_flags;
	char	**envp;

	tmp = getcwd(NULL, 0);
	exec = ft_strjoin(tmp, cmd->value + 1);
	free(tmp);
	if (access(exec, F_OK) == 0 && access(exec, X_OK) == 0)
	{
		exec_flags = get_exec_flags(cmd);
		envp = get_exec_env(&central->dupenv);
		execve(exec, exec_flags, envp);
		clean_all(central);
		cmd_remainder_cleanup(envp, exec_flags, central);
		exit(1);
	}
	return (127);
}

/**
 * @brief Executes commands when PATH is unset and the terminal
 *  demands absolute path executables only.
 */
int	do_absolute(t_central *central, t_input *cmd)
{
	int	i;

	if (ft_strchr(cmd->value, '/'))
		i = do_received_cmd(central, cmd);
	else
		i = do_local(central, cmd);
	if (i != 0)
	{
		not_dir(cmd->value);
		exit(i);
	}
	exit(0);
}
