/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:56:13 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/04 16:20:19 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	const char	*prompt = "sh-5.2$ ";
	char		*rl;
	char		**split;

	(void)ac;
	(void)av;
	while (11)
	{
		rl = readline(prompt);
		add_history(rl);
		split = ft_split(rl, ' ');
		if (!split)
			return (1);
		if (!split[0])
			printf("");
		else if (ft_strncmp(split[0], "echo", 4) == 0)
			ft_echo(split);
		else if (ft_strncmp(split[0], "cd", 2) == 0)
			ft_cd(split, ft_getenv("HOME", env));
		else if (ft_strncmp(split[0], "pwd", 2) == 0)
			ft_pwd();
		else
			printf("%s: command not found\n", split[0]);
		free(rl);
	}
}
