/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:57:18 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/09 14:05:03 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd_oldpwd(t_central *central)
{
	t_envp	*tmp_env;
	char	*tmp_str;

	tmp_env = ft_getenv(&central->dupenv, "OLDPWD");
	if (!tmp_env)
	{
		no_oldpwd();
		central->exit_val = 1;
		return ;
	}
	tmp_str = ft_strjoin(tmp_env->value, "\n");
	write(1, tmp_str, ft_strlen(tmp_str));
	free(tmp_str);
	chdir(tmp_env->value);
	set_old_pwd(&central->dupenv);
	set_pwd(&central->dupenv);
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
	int		i;
	int		count;
	t_envp	*tmp;

	tmp = *dupenv;
	while (ft_strcmp("PWD", tmp->var))
		tmp = tmp->next;
	i = 0;
	count = 0;
	while (tmp->value[i])
	{
		if (tmp->value[i] == '/')
			count++;
		i++;
	}
	if (ft_strcmp("/", tmp->value) == 0)
		return ;
	else if (count == 1 && tmp->value[1] != '\0')
	{
		free(tmp->value);
		tmp->value = ft_strdup("/");
	}
	else
		set_bpwd(dupenv, count);
}
