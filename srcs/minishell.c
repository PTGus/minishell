/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:56:13 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/14 17:11:36 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	const char	*prompt;
	char		*rl;
	char		**split;
	t_envp		**dupenv;

	(void)ac;
	(void)av;
	dupenv = ft_calloc(1, sizeof(t_envp));
	duplicate_env(dupenv, env);
	handle_signals();
	while (11)
	{
		prompt = "sh-5.2$ ";
		rl = readline(prompt);
		add_history(rl);
		if (rl == NULL)
		{
			printf("exit\n");
			return (0);
		}
		else
		{
			split = ft_split(rl, ' ');
			if (!split)
				return (1);
			if (!split[0])
				continue ;
			else
				do_cmd(split, dupenv);
			ft_free_split(split);
		}
		free(rl);
	}
}

void	do_cmd(char **split, t_envp **dupenv)
{
	if (ft_strcmp(split[0], "echo") == 0)
		ft_echo(split);
	else if (ft_strcmp(split[0], "cd") == 0)
		ft_cd(split, dupenv);
	else if (ft_strcmp(split[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(split[0], "env") == 0)
		ft_env(dupenv);
	// else if (ft_strcmp(split[0], "export") == 0)
	// 	ft_export(split, dupenv);
	else
		printf("%s: command not found\n", split[0]);
}
