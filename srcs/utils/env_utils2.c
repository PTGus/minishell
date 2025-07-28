/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:23:58 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/28 16:56:29 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_empty_env(t_envp **dupenv)
{
	char	*tmp;
	char	*tmp2;
	t_envp	*tmp_env;

	ft_lst_back(dupenv, new_env("_=/usr/bin/env"));
	tmp = getcwd(NULL, 0);
	tmp2 = ft_strjoin("PWD=", tmp);
	free(tmp);
	ft_lst_back(dupenv, new_env(tmp2));
	free(tmp2);
	tmp_env = ft_calloc(1, sizeof(t_envp));
	tmp_env->visible_env = FALSE;
	tmp_env->has_equal = FALSE;
	tmp_env->index = -1;
	tmp_env->value = NULL;
	tmp_env->var = ft_strdup("OLDPWD");
	tmp_env->next = NULL;
	tmp_env->prev = NULL;
	ft_lst_back(dupenv, tmp_env);
	organise_env(dupenv);
}

char	*segment_env(char *envp, int idx)
{
	char	*ret;
	int		j;

	ret = ft_calloc(idx + 1, sizeof(char));
	if (!ret)
		return (NULL);
	j = 0;
	while (j < idx)
	{
		ret[j] = envp[j];
		j++;
	}
	return (ret);
}
