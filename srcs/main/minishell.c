/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:56:13 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/27 13:31:03 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief An infinte loop that receives a string
 *  passed though the terminal and utilizes it as paramters.
 * @param central A struct that contains pointers to
 *  all the neccessary variables and lists.
 */
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
			ctrl_d(central);
		if (rl[0] == '\0')
		{
			free(rl);
			continue ;
		}
		add_history(rl);
		ft_parse(rl, central);
		split = ft_split(rl, ' ');
		do_cmd(split, central);
		ft_freesplit(split);
		free(rl);
	}
}

int	main(int ac, char **av, char **env)//
{
	t_envp		**dupenv;
	t_central	*central;

	if (ac == 1)
	{
		dupenv = ft_calloc(1, sizeof(t_envp *));
		central = ft_calloc(1, sizeof(t_central));
		duplicate_env(dupenv, env);
		init_central(central, dupenv);
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

/**
 * @brief An infinte loop that receives a string
 *  passed though the terminal and utilizes it as paramters.
 * @param central A struct that contains pointers to
 *  all the neccessary variables and lists.
 */
void	rl_loop(t_central *central)
{
	const char	*prompt;
	char		*rl;
	char		**split;

	prompt = "minishell$ ";
	reset_fds(0);
	while (1)
	{
		rl = readline(prompt);
		if (rl == NULL)
			ctrl_d(central);
		if (rl[0] == '\0')
		{
			free(rl);
			continue ;
		}
		add_history(rl);
		split = ft_split(rl, ' ');
		has_shell_operator(central, split);
		ft_freesplit(split);
		free(rl);
		reset_fds(1);
	}
	reset_fds(2);
}

/**
 * @brief Checks if a command passed through realine
 *  is one of the built_in functions or not.
 * @param central A struct that contains pointers to
 *  all the neccessary variables and lists.
 * @param split An array of arrays with the prompt received from read line.
 */
int	is_built_in(t_central *central, char **split)
{
	if (ft_strcmp(split[0], "echo") == 0)
		return (ft_echo(central, split), 0);
	else if (ft_strcmp(split[0], "cd") == 0)
		return (ft_cd(central, split), 0);
	else if (ft_strcmp(split[0], "pwd") == 0)
		return (ft_pwd(central), 0);
	else if (ft_strcmp(split[0], "env") == 0)
		return (ft_env(central, split), 0);
	else if (ft_strcmp(split[0], "export") == 0)
		return (ft_export(central, split), 0);
	else if (ft_strcmp(split[0], "exit") == 0)
		return (ft_exit(central, split[1]), 0);
	else if (ft_strcmp(split[0], "unset") == 0)
		return (ft_unset(central, split[1]), 0);
	else
		return (1);
}

/**
 * @brief Checks if PATH exists if it does it executes the command.
 * @param split An array of arrays with the prompt received from read line.
 * @param central A struct that contains pointers to
 *  all the neccessary variables and lists.
 */
void	do_cmd(t_central *central, char **split)
{
	t_envp	*tmp;

	tmp = central->dupenv;
	while (tmp != NULL && ft_strcmp(tmp->var, "PATH") != 0)
		tmp = tmp->next;
	if (!tmp)
	{
		not_dir(split[0]);
		central->exit_val = 127;
		return ;
	}
	if (is_built_in(central, split) == 0)
		return ;
	else
		commander(central, split);
}
