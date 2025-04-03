/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:56:13 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/03 17:24:35 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	const char	*prompt = "sh-5.2$ ";
	char		*rl;
	char		**split;

	while (11)
	{
		rl = readline(prompt);
		add_history(rl);
		split = ft_split(rl, ' ');
		if (access(ft_strjoin("~/bin/", split[0]), X_OK | F_OK) == 0)
		{
			execve(ft_strjoin("~/bin/", split[0]), );
		}
		free(rl);
	}
}
