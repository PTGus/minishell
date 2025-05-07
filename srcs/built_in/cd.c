/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:14:43 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/07 16:07:50 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Built-in command that behaves exactly like the command "cd".
 * @param split The command arguments (where to go).
 * @param home_path The path to the home directory in case the
 *  is called to travel to home.
 */
void	ft_cd(char **split, t_central *central)
{
	t_envp		*temp;

	if ((split[1] != NULL && access(split[1], F_OK) == 0) \
		|| (split[1][0] == '~' && split[1][1] == '\0'))
	{
		temp = central->dupenv;
		set_old_pwd(&central->dupenv);
		set_home(&central->dupenv);
		while (ft_strcmp(temp->var, "HOME") != 0)
			temp = temp->next;
		chdir(temp->value);
	}
	else if (access(split[1], F_OK) < 0)
	{
		printf("bash: cd: %s: No such file or directory\n", split[1]);
		central->exit_val = 1;
		return ;
	}
	else
	{
		set_old_pwd(&central->dupenv);
		set_pwd(&central->dupenv, split[1]);
		chdir(split[1]);
	}
	central->exit_val = 0;
}

/**
 * @brief Sets the "PWD" variable's value to home (/home/(username)).
 * @param dupenv A duplicate of the original envp.
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
 * @param dupenv A duplicate of the original envp.
 */
void	set_pwd(t_envp **dupenv, char *path)
{
	t_envp	*pwd;
	char	*tmp;

	pwd = *dupenv;
	while (ft_strcmp(pwd->var, "PWD") != 0)
		pwd = pwd->next;
	tmp = ft_strdup(pwd->value);
	free(pwd->value);
	pwd->value = NULL;
	path = ft_strjoin("/", path);
	pwd->value = ft_strjoin(tmp, path);
	free(tmp);
	free(path);
}

/**
 * @brief Sets the "OLDPWD" variable's value to the
 *  previous currently working directory (CWD).
 * @param dupenv A duplicate of the original envp.
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
