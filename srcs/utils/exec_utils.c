/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:12:19 by gumendes          #+#    #+#             */
/*   Updated: 2025/06/30 11:25:53 by gumendes         ###   ########.fr       */
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

char	**strip_redirs(char **tok);

void	do_solo(t_central *central, char **split)
{
	pid_t	pid;
	int		status;
	int		pipe_fd[2];

	if (is_built_in(split[0]) == 0)
	{
		do_builtin(central, split);
		return ;
	}
	pipe(pipe_fd);
	pid = fork();
	status = 0;
	if (pid == 0)
	{
		has_to_redirect(central, split);
		do_cmd(central, strip_redirs(split));
	}
	else
		waitpid(-1, &status, 0);
	central->exit_val = (status >> 8) & 0xFF;;
}

int	is_built_in(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (0);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "env") == 0)
		return (0);
	else if (ft_strcmp(cmd, "export") == 0)
		return (0);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (0);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (0);
	else
		return (1);
}
