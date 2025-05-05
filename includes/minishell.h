/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:42:20 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/30 16:09:22 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <errno.h>
# include <signal.h>
# include "../libft/libft.h"

typedef struct s_envp
{
	struct s_envp	*next;
	struct s_envp	*prev;
	char			*var;
	char			*value;
	int				index;
}	t_envp;

//--------------------------------------------------------------//

int		main(int ac, char **av, char **env);
void	do_cmd(char **split, t_envp **dupenv);
void	handle_signals(void);

//--------------------------------------------------------------//

// BUILT-IN //

// cd //
void	ft_cd(char **split, t_envp **dupenv);
void	set_pwd(t_envp **dupenv, char *path);
void	set_old_pwd(t_envp **dupenv);
void	set_home(t_envp **dupenv);

// echo //
void	ft_echo(char **split);

// env //
void	ft_env(t_envp **dupenv);
t_envp	*new_env(char *envp);
int		init_env(t_envp **dupenv, char **envp);
int		duplicate_env(t_envp **dupenv, char **envp);

// exit //
void	ft_exit(t_envp **dupenv, char *exit_val);

// export //
void	ft_export(char **split, t_envp **dupenv);
int		should_revalue(t_envp **dupenv, char**split);
void	insert_before_last(t_envp **dupenv, t_envp *curr);

// pwd //
void	ft_pwd(void);

// unset //
void	ft_unset(t_envp **dupenv, char *to_unset);

//--------------------------------------------------------------//

// CLEAN_UP //

// free //
void	ft_envfreeone(t_envp *dupenv);
void	free_env(t_envp **dupenv);
void	ft_freesplit(char **split);

//--------------------------------------------------------------//

// COMMANDS //

// executer //
int		commander(t_envp **dupenv, char **split);
void	executer(char *exec, char **split, t_envp **dupenv);
char	*pather(t_envp *path, char *cmd);

//--------------------------------------------------------------//

// UTILS //

// env_utils //
void	organise_env(t_envp **dupenv);
void	reorder_dupenv(t_envp **dupenv);
void	env_delone(t_envp *to_del);

// exec_utils //
char	*get_line(t_envp *dupenv);
char	**get_exec_env(t_envp **dupenv);

// lst_utils //
void	ft_lst_back(t_envp **dupenv, t_envp *curr);
t_envp	*lstlast(t_envp *dupenv);

// utils //
int		ft_strcmp(char *s1, char *s2);

//--------------------------------------------------------------//

#endif
