/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:14:43 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/09 15:43:29 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Built-in command that behaves exactly like the command "cd".
  * @param split An array of arrays with the prompt received from read line.
 * @param home_path The path to the home directory in case the
 *  is called to travel to home.
 */
void	ft_cd(char **split, t_central *central)
{
	t_envp	*temp;

	if ((split[1] == NULL && access(split[1], F_OK) != 0) \
		|| (split[1][0] == '~' && split[1][1] == '\0'))
	{
		temp = central->dupenv;
		set_old_pwd(&central->dupenv);
		set_home(&central->dupenv);
		while (ft_strcmp(temp->var, "HOME") != 0)
			temp = temp->next;
		chdir(temp->value);
	}
	else if (access(split[1], F_OK) == 0)
		set_cd_values(&central->dupenv, split);
	else
	{
		not_dir(split[1]);
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
void	set_cd_values(t_envp **dupenv, char **split)
{
	if (ft_strcmp("..", split[1]) == 0)
	{
		set_old_pwd(dupenv);
		set_back(dupenv);
		chdir(split[1]);
	}
	else
	{
		set_old_pwd(dupenv);
		set_pwd(dupenv, split[1]);
		chdir(split[1]);
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
