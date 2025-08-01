/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:57:18 by gumendes          #+#    #+#             */
/*   Updated: 2025/08/01 14:14:57 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd_oldpwd(t_central *central)
{
	t_envp	*tmp_env;
	char	*tmp;

	tmp_env = ft_getenv(&central->dupenv, "OLDPWD");
	if (!tmp_env)
	{
		no_oldpwd();
		central->exit_val = 1;
		return ;
	}
	write(1, tmp_env->value, ft_strlen(tmp_env->value));
	write(1, "\n", 1);
	tmp = ft_strdup(tmp_env->value);
	set_old_pwd(&central->dupenv);
	chdir(tmp);
	free(tmp);
	set_pwd(&central->dupenv);
	central->exit_val = 0;
}

void	cd_to_home(t_central *central)
{
	t_envp	*tmp_env;

	tmp_env = ft_getenv(&central->dupenv, "HOME");
	if (!tmp_env)
		return (no_home(), central->exit_val = 1, (void) 0);
	set_old_pwd(&central->dupenv);
	set_home(&central->dupenv);
	chdir(tmp_env->value);
	central->exit_val = 0;
}

/**
 * @brief Sets the PWD to the previous directory.
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 * @param count How many paths the pwd should have.
 */
void	set_bpwd(t_envp **dupenv, int count)
{
	int		i;
	int		flag;
	char	*tmp;
	t_envp	*pwd;

	pwd = *dupenv;
	while (ft_strcmp("PWD", pwd->var))
		pwd = pwd->next;
	i = 0;
	flag = 0;
	while (flag != count)
	{
		if (pwd->value[i] == '/')
			flag++;
		i++;
	}
	tmp = ft_strdup(pwd->value);
	if (!tmp)
		return ;
	free(pwd->value);
	pwd->value = ft_substr(tmp, 0, i - 1);
	free(tmp);
}

/**
 * @brief Finds out which path should be displayed in PWD when
 *  the program uses "cd" to go to pre previous directory.
 * @param dupenv A linked list with the duplicated envp stored whitin it.
 */
void	set_back(t_envp **dupenv)
{
	t_envp	*pwd;

	pwd = ft_getenv(dupenv, "PWD");
	if (!pwd)
		return ;
	if (pwd->value)
		free(pwd->value);
	pwd->value = getcwd(NULL, 0);
	pwd->has_equal = TRUE;
	pwd->visible_env = TRUE;
}
