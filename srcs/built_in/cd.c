/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:14:43 by gumendes          #+#    #+#             */
/*   Updated: 2025/06/30 15:38:01 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Built-in command that behaves exactly like the command "cd".
  * @param split An array of arrays with the prompt received from read line.
 * @param home_path The path to the home directory in case the
 *  is called to travel to home.
 */
void	ft_cd(t_central *central, t_input *cmd)
{
	t_envp	*tmp_env;
	t_input	*tmp_cmd;

	tmp_cmd = cmd;
	while (ft_strcmp(tmp_cmd->value, "cd") != 0)
		tmp_cmd = tmp_cmd->next;
	if ((tmp_cmd->next == NULL && access(tmp_cmd->next->value, F_OK) != 0) \
		|| (tmp_cmd->next->value[0] == '~' && tmp_cmd->next->value[1] == '\0')) // this has different behaviours deppending if its used as "cd" (doesnt work without HOME set) or "cd ~" (works without HOME set)
	{
		set_old_pwd(&central->dupenv);
		set_home(&central->dupenv);
		tmp_env = ft_getenv(&central->dupenv, "HOME");
		chdir(tmp_env->value);
	}
	else if (access(tmp_cmd->next->value, F_OK) == 0)
		set_cd_values(&central->dupenv, tmp_cmd);
	else
	{
		not_dir(tmp_cmd->next->value);
		central->exit_val = 1;
		return ;
	}
	central->exit_val = 0;
}

/**
 * @brief Finds out whether the command is prompting the prompting
 *  the process to go to a defined directory or to the previous directory.
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 * @param split An array of arrays with the prompt received from read line.
 */
void	set_cd_values(t_envp **dupenv, t_input *cmd)
{
	t_input	*tmp;

	tmp = cmd;
	if (ft_strcmp("..", tmp->next->value) == 0)
	{
		set_old_pwd(dupenv);
		set_back(dupenv);
		chdir(tmp->next->value);
	}
	else
	{
		set_old_pwd(dupenv);
		set_pwd(dupenv, tmp->next->value);
		chdir(tmp->next->value);
	}
}

/**
 * @brief Sets the "PWD" variable's value to home (/home/(username)).
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 */
void	set_home(t_envp **dupenv)
{
	t_envp	*pwd;
	t_envp	*home;

	pwd = *dupenv;
	home = *dupenv;
	while (ft_strcmp(pwd->var, "PWD") != 0)
		pwd = pwd->next;
	while (ft_strcmp(home->var, "HOME") != 0)
		home = home->next;
	free(pwd->value);
	pwd->value = ft_strdup(home->value);
}

/**
 * @brief Sets the "PWD" variable's value
 *  to the currently working directory (CWD).
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 */
void	set_pwd(t_envp **dupenv, char *path)
{
	t_envp	*pwd;
	char	*tmp;
	int		i;

	pwd = *dupenv;
	while (ft_strcmp(pwd->var, "PWD") != 0)
		pwd = pwd->next;
	tmp = ft_strdup(pwd->value);
	free(pwd->value);
	if (strcmp(path, "..") == 0)
	{
		set_back(dupenv);
		return ;
	}
	i = -1;
	while (path[++i])
	{
		if (path[i] == '/')
			break ;
	}
	path[i] = '\0';
	path = ft_strjoin("/", path);
	pwd->value = ft_strjoin(tmp, path);
	free(tmp);
	free(path);
}

/**
 * @brief Sets the "OLDPWD" variable's value to the
 *  previous currently working directory (CWD).
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 */
void	set_old_pwd(t_envp **dupenv)
{
	t_envp		*old_pwd;

	old_pwd = *dupenv;
	while (ft_strcmp(old_pwd->var, "OLDPWD") != 0)
		old_pwd = old_pwd->next;
	free(old_pwd->value);
	old_pwd->value = ft_strdup(getcwd(NULL, 0));
}
