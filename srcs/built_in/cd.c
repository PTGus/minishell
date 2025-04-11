/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:14:43 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/11 15:33:11 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Built-in command that behaves exactly like the command "cd".
 * @param split The command arguments (where to go).
 * @param home_path The path to the home directory in case the is called to travel to home.
 */
void	ft_cd(char **split, t_envp **dupenv)
{
	char	*home;
	t_envp	*temp;

	if (split[1] == NULL || (split[1][0] == '~' && split[1][1] == '\0'))
	{
		temp = *dupenv;
		while (ft_strcmp(temp->var, "HOME") != 0)
			temp = temp->next;
		home = ft_strjoin(temp->var, temp->value);
		chdir(home);
		free(home);
		return ;
	}
	if (access(split[1], X_OK) < 0)
		printf("bash: cd: %s: No such file or directory\n", split[1]);
	else
		chdir(split[1]);
}
