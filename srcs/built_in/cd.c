/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:14:43 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/24 17:18:20 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Built-in command that behaves exactly like the command "cd".
 * @param split The command arguments (where to go).
 * @param home_path The path to the home directory in case the
 *  is called to travel to home.
 */
void	ft_cd(char **split, t_envp **dupenv)
{
	t_envp		*temp;

	if (split[1] == NULL || (split[1][0] == '~' && split[1][1] == '\0'))
	{
		temp = *dupenv;
		set_old_pwd(dupenv);
		set_home(dupenv);
		while (ft_strcmp(temp->var, "HOME") != 0)
			temp = temp->next;
		chdir(temp->value);
		return ;
	}
	else if (access(split[1], F_OK) < 0)
		printf("bash: cd: %s: No such file or directory\n", split[1]);
	else
	{
		set_old_pwd(dupenv);
		set_pwd(dupenv, split[1]);
		chdir(split[1]);
	}
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
