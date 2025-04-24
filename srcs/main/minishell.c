/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:56:13 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/24 11:37:52 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rl_loop(t_envp **dupenv)
{
	const char	*prompt;
	char		*rl;
	char		**split;

	prompt = "minishell$ ";
	while (11)
	{
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
			if (!split[0])
				continue ;
			else
				do_cmd(split, dupenv);
			ft_freesplit(split);
		}
		free(rl);
	}
}

int	main(int ac, char **av, char **env)
{
	t_envp		**dupenv;

	(void)ac;
	(void)av;
	dupenv = ft_calloc(1, sizeof(t_envp));
	duplicate_env(dupenv, env);
	handle_signals();
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
	else if (ft_strcmp(split[0], "export") == 0)
		ft_export(split, dupenv);
	else if (ft_strcmp(split[0], "exit") == 0)
		ft_exit(dupenv);
	else if (ft_strcmp(split[0], "unset") == 0)
		ft_unset(dupenv, split[1]);
	else
		printf("%s: command not found\n", split[0]);
}
