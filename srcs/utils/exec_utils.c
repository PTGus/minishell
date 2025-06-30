/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:12:19 by gumendes          #+#    #+#             */
/*   Updated: 2025/06/30 16:58:49 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Transforms into a string, the dupenv node's variable and value.
 * @param dupenv A linked list with the duplicated envp stored whitin it.
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
 * @param dupenv A linked list with the duplicated envp stored whitin it.
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

int	is_relative(char *cmd)
{
	if (ft_strncmp(cmd, "./", 2) == 0)
		return (0);
	return (1);
}

void	do_solo(t_central *central, t_input *cmd)
{
	pid_t	pid;
	t_input	*tmp;
	int		status;
	int		pipe_fd[2];

	tmp = cmd;
	if (is_built_in(cmd) == 0)
	{
		do_builtin(central, cmd);
		return ;
	}
	pipe(pipe_fd);
	pid = fork();
	status = 0;
	if (pid == 0)
	{
		has_to_redirect(central, cmd);
		do_cmd(central, cmd);
	}
	else
		waitpid(-1, &status, 0);
	central->exit_val = (status >> 8) & 0xFF;;
}

int	is_built_in(t_input *cmd)
{
	t_input *tmp;

	tmp = cmd;
	while (tmp)
	{
		if (ft_strcmp(tmp->value, "echo") == 0)
			return (0);
		else if (ft_strcmp(tmp->value, "cd") == 0)
			return (0);
		else if (ft_strcmp(tmp->value, "pwd") == 0)
			return (0);
		else if (ft_strcmp(tmp->value, "env") == 0)
			return (0);
		else if (ft_strcmp(tmp->value, "export") == 0)
			return (0);
		else if (ft_strcmp(tmp->value, "exit") == 0)
			return (0);
		else if (ft_strcmp(tmp->value, "unset") == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
