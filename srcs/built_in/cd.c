/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:14:43 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/21 17:38:31 by gumendes         ###   ########.fr       */
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
	t_input	*tmp_cmd;

	tmp_cmd = cmd;
	while (tmp_cmd && ft_strcmp(tmp_cmd->value, "cd") != 0)
		tmp_cmd = tmp_cmd->next;
	if (tmp_cmd->next == NULL
		|| (tmp_cmd->next->value[0] == '~' && tmp_cmd->next->value[1] == '\0'))
		cd_to_home(central);
	else if (tmp_cmd->next->next)
		return (central->exit_val = 1,
			excessive_args(tmp_cmd->next->next->value), (void) 0);
	else if (ft_strcmp(tmp_cmd->next->value, "-") == 0)
		cd_oldpwd(central);
	else if (access(tmp_cmd->next->value, F_OK) == 0)
		set_cd_values(&central->dupenv, tmp_cmd);
	else
		return (not_cd_dir(tmp_cmd->next->value),
			central->exit_val = 1, (void) 0);
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
		chdir(tmp->next->value);
		set_pwd(dupenv);
	}
}

/**
 * @brief Sets the "PWD" variable's value to home (/home/(username)).
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 */
void	set_home(t_envp **dupenv)
{
	t_envp		*pwd;
	t_envp		*home;

	pwd = *dupenv;
	pwd = ft_getenv(dupenv, "PWD");
	if (pwd != NULL)
	{
		home = *dupenv;
		home = ft_getenv(dupenv, "HOME");
		free(pwd->value);
		pwd->value = ft_strdup(home->value);
	}
}

/**
 * @brief Sets the "PWD" variable's value
 *  to the currently working directory (CWD).
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 */
void	set_pwd(t_envp **dupenv)
{
	t_envp	*pwd;
	char	*tmp;
	char	*new_val;

	pwd = ft_getenv(dupenv, "PWD");
	if (!pwd)
		return ;
	tmp = getcwd(NULL, 0);
	if (!tmp)
		return ;
	new_val = ft_strdup(tmp);
	if (!new_val)
	{
		free(tmp);
		return ;
	}
	free(pwd->value);
	pwd->value = new_val;
	free(tmp);
}

/**
 * @brief Sets the "OLDPWD" variable's value to the
 *  previous currently working directory (CWD).
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 */
void	set_old_pwd(t_envp **dupenv)
{
	t_envp		*old_pwd;

	old_pwd = ft_getenv(dupenv, "OLDPWD");
	free(old_pwd->value);
	old_pwd->value = ft_strdup(getcwd(NULL, 0));
}
