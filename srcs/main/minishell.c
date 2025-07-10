/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:56:13 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/10 16:42:27 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_signal = 0;

void	rl_loop(t_central *central);

int	main(int ac, char **av, char **env)
{
	t_envp		**dupenv;
	t_central	*central;
	int	exit_v;

	if (ac == 1)
	{
		dupenv = ft_calloc(1, sizeof(t_envp *));
		central = ft_calloc(1, sizeof(t_central));
		duplicate_env(dupenv, env);
		increase_shlvl(dupenv);
		init_central(central, dupenv);
		reset_fds(0);
		handle_signals();
		rl_loop(central);
		reset_fds(2);
		rl_clear_history();
		exit_v = central->exit_val;
		clean_all(central);
		return (free(dupenv), exit_v);
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
	char		*rl;

	while (1)
	{
		rl = readline("minishell$ ");
		if (rl == NULL)
			return (ctrl_d(), (void)0);
		if (rl[0] == '\0')
		{
			free(rl);
			continue ;
		}
		if (g_signal == 130)
		{
			central->exit_val = g_signal;
			g_signal = 0;
		}
		add_history(rl);
		ft_parse(rl, central);
		has_shell_operator(central);
		if (central->has_exited == TRUE)
			return ;
		post_loop_cleanup(central, rl);
	}
}

/**
 * @brief Checks if a command passed through realine
 *  is one of the built_in functions or not.
 * @param central A struct that contains pointers to
 *  all the neccessary variables and lists.
 * @param split An array of arrays with the prompt received from read line.
 */
int	do_builtin(t_central *central, t_input *cmd)
{
	t_input	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (ft_strcmp(tmp->value, "echo") == 0)
			return (ft_echo(central, cmd), 0);
		else if (ft_strcmp(tmp->value, "cd") == 0)
			return (ft_cd(central, cmd), 0);
		else if (ft_strcmp(tmp->value, "pwd") == 0)
			return (ft_pwd(central), 0);
		else if (ft_strcmp(tmp->value, "env") == 0)
			return (ft_env(central, cmd), 0);
		else if (ft_strcmp(tmp->value, "export") == 0)
			return (ft_export(central, cmd), 0);
		else if (ft_strcmp(tmp->value, "exit") == 0)
			return (ft_exit(central, tmp), 0);
		else if (ft_strcmp(tmp->value, "unset") == 0)
			return (ft_unset(central, tmp->next), 0);
		tmp = tmp->next;
	}
	return (1);
}

/**
 * @brief Checks if PATH exists if it does it executes the command.
 * @param split An array of arrays with the prompt received from read line.
 * @param central A struct that contains pointers to
 *  all the neccessary variables and lists.
 */
void	do_cmd(t_central *central, t_input *cmd)
{
	if (is_built_in(cmd) == 0)
	{
		do_builtin(central, cmd);
		return ;
	}
	else
		commander(central, cmd);
}
