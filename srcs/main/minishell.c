/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:56:13 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/30 16:09:22 by gumendes         ###   ########.fr       */
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
			return ;
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

	if (ac == 1)
	{
		dupenv = ft_calloc(1, sizeof(t_envp));
		duplicate_env(dupenv, env);
		handle_signals();
		rl_loop(dupenv);
		free_env(dupenv);
		return (0);
	}
	else
		printf("bash: %s: No such file or directory\n", av[1]);
}

int	is_built_in(t_envp **dupenv, char **split)
{
	if (ft_strcmp(split[0], "echo") == 0)
		return (ft_echo(split), 0);
	else if (ft_strcmp(split[0], "cd") == 0)
		return (ft_cd(split, dupenv), 0);
	else if (ft_strcmp(split[0], "pwd") == 0)
		return (ft_pwd(), 0);
	else if (ft_strcmp(split[0], "env") == 0)
		return (ft_env(dupenv), 0);
	else if (ft_strcmp(split[0], "export") == 0)
		return (ft_export(split, dupenv), 0);
	else if (ft_strcmp(split[0], "exit") == 0)
		return (ft_exit(dupenv, split[1]), 0);
	else if (ft_strcmp(split[0], "unset") == 0)
		return (ft_unset(dupenv, split[1]), 0);
	else
		return (1);
}

void	do_cmd(char **split, t_envp **dupenv)
{
	if (is_built_in(dupenv, split) == 0)
		return ;
	else
		commander(dupenv, split);
}
