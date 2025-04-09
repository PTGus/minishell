/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:56:13 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/09 17:18:27 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	// const char	*prompt;
	// char		*rl;
	// char		**split;
	t_envp		*dupenv = NULL;

	(void)ac;
	(void)av;
	dupenv = malloc(sizeof(t_envp));
	duplicate_env(&dupenv, env);
	while (dupenv != NULL)
	{
		printf("%s=%s\n", dupenv->var, dupenv->value);
		dupenv = dupenv->next;
	}
/* 	handle_signals();
	dupenv = ft_calloc(1, sizeof(t_envp));
	duplicate_env(dupenv, env);
	while (11)
	{
		prompt = ft_strjoin(ft_strjoin("sh-5.2:~/", ft_substr(getcwd(NULL, 0), 15, 999)), "$ ");
		rl = readline(prompt);
		add_history(rl);
		if (rl == NULL)
		{
			printf("exit\n");
			return (0);
		}
		if (getenv("PATH") == NULL)
			printf("bash: %s: No such file or directory\n", split[0]);
		else
		{
			split = ft_split(rl, ' ');
			if (!split)
				return (1);
			if (!split[0])
				printf("");
			else if (ft_strcmp(split[0], "echo") == 0)
				ft_echo(split);
			else if (ft_strcmp(split[0], "cd") == 0)
				ft_cd(split, getenv("HOME"));
			else if (ft_strcmp(split[0], "pwd") == 0)
				ft_pwd();
			else if (ft_strcmp(split[0], "env") == 0)
				ft_env(env);
			else
				printf("%s: command not found\n", split[0]);
		}
		free(rl);
	} */
}
