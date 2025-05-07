/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:56:13 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/07 17:45:58 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rl_loop(t_central *central)
{
	const char	*prompt;
	char		*rl;
	char		**split;

	prompt = "minishell$ ";
	while (1)
	{
		rl = readline(prompt);
		if (rl == NULL)
		{
			printf("exit\n");
			rl_clear_history();
			return ;
		}
		if (rl[0] == '\0')
			continue ;
		add_history(rl);
		split = ft_split(rl, ' ');
		if (!split[0])
		{
			free(split);
			continue ;
		}
		else
			do_cmd(split, central);
		ft_freesplit(split);
		free(rl);
	}
}

int	main(int ac, char **av, char **env)
{
	t_envp		**dupenv;
	t_central	*central;

	if (ac == 1)
	{
		dupenv = ft_calloc(1, sizeof(t_envp *));
		central = ft_calloc(1, sizeof(t_central));
		duplicate_env(dupenv, env);
		init_central(central);
		central->dupenv = *dupenv;
		handle_signals();
		rl_loop(central);
		clean_all(central);
		return (0);
	}
	else
	{
		printf("bash: %s: No such file or directory\n", av[1]);
		return (127);
	}
}

int	is_built_in(t_central *central, char **split)
{
	if (ft_strcmp(split[0], "echo") == 0)
		return (ft_echo(split, central), 0);
	else if (ft_strcmp(split[0], "cd") == 0)
		return (ft_cd(split, central), 0);
	else if (ft_strcmp(split[0], "pwd") == 0)
		return (ft_pwd(central), 0);
	else if (ft_strcmp(split[0], "env") == 0)
		return (ft_env(split, central), 0);
	else if (ft_strcmp(split[0], "export") == 0)
		return (ft_export(split, central), 0);
	else if (ft_strcmp(split[0], "exit") == 0)
		return (ft_exit(central, split[1]), 0);
	else if (ft_strcmp(split[0], "unset") == 0)
		return (ft_unset(central, split[1]), 0);
	else
		return (1);
}

void	do_cmd(char **split, t_central *central)
{
	t_envp	*tmp;

	tmp = central->dupenv;
	while (tmp != NULL && ft_strcmp(tmp->var, "PATH") != 0)
		tmp = tmp->next;
	if (!tmp)
	{
		printf("bash: %s: No such file or directory\n", split[0]);
		central->exit_val = 127;
		return ;
	}
	if (is_built_in(central, split) == 0)
		return ;
	else
		commander(central, split);
}
