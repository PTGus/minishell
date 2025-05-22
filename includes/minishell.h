/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:42:20 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/22 17:11:25 by gumendes         ###   ########.fr       */
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
# include <fcntl.h>
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

typedef struct s_central
{
	struct s_envp	*dupenv;
	int				exit_val;
}	t_central;

typedef struct s_envp
{
	struct s_envp	*next;
	struct s_envp	*prev;
	char			*var;
	char			*value;
	int				index;
	int				visible_env;
}	t_envp;

//--------------------------------------------------------------//

// BUILT-IN //

// cd //
void	ft_cd(t_central *central, char **split);
void	set_cd_values(t_envp **dupenv, char **split);
void	set_pwd(t_envp **dupenv, char *path);
void	set_old_pwd(t_envp **dupenv);
void	set_home(t_envp **dupenv);

// echo //
void	ft_echo(t_central *central, char **split);
void	echo_n(char **split);

// env //
void	ft_env(t_central *central, char **split);
t_envp	*new_env(char *envp);
int		init_env(t_envp **dupenv, char **envp);
int		duplicate_env(t_envp **dupenv, char **envp);

// exit //
void	ft_exit(t_central *central, char *exit_val);

// export //
int		should_revalue(t_envp **dupenv, char**split);
void	declarex(t_envp **dupenv);
void	ft_export(t_central *central, char **split);
void	hidden_export(t_central *central, char **split);

// pwd //
void	ft_pwd(t_central *central);

// unset //
void	ft_unset(t_central *central, char *to_unset);

//--------------------------------------------------------------//

// CLEAN_UP //

// free //
void	clean_all(t_central *central);
void	ft_envfreeone(t_envp *dupenv);
void	free_env(t_envp **dupenv);
void	ft_freesplit(char **split);

//--------------------------------------------------------------//

// COMMANDS //

// executer //
int		commander(t_central *central, char **split);
void	executer(char *exec, t_central *central, char **split);
char	*pather(t_envp *path, char *cmd);

//--------------------------------------------------------------//

// ERR_HANDLING //

// errors //
void	comm_not_foud(char *str);
void	not_dir(char *str);

//--------------------------------------------------------------//

// MAIN //

// minishell //
int		main(int ac, char **av, char **env);
void	do_cmd(t_central *central, char **split);
void	rl_loop(t_central *central);
int		is_built_in(t_central *central, char **split);

//--------------------------------------------------------------//

// PIPES //

// pipe //
void	execute_pipes(t_central *central, char **split, int pipe_fd[][2], int curr_index, int pipe_amm);
void	piper(t_central *central, char **split, int pipe_amm);

//--------------------------------------------------------------//

// SIGNALS //

// signals //
void	ctrl_c(int sig);
void	ctrl_d(t_central *central);
void	handle_signals(void);

//--------------------------------------------------------------//
// UTILS //

// cd_utils //
void	set_back(t_envp **pwd);

// central_utils //
void	init_central(t_central *central, t_envp **dupenv);

// env_utils //
void	organise_env(t_envp **dupenv);
void	reorder_dupenv(t_envp **dupenv);
void	env_delone(t_envp *to_del);
void	insert_before_last(t_envp **dupenv, t_envp *curr);

// exec_utils //
char	*get_line(t_envp *dupenv);
char	**get_exec_env(t_envp **dupenv);

// export utils //
void	print_declaration(t_envp *curr);
void	hidden_export(t_central *central, char **split);

// list_utils //
void	ft_lst_back(t_envp **dupenv, t_envp *curr);
t_envp	*lstlast(t_envp **dupenv);

// pipe_utils //
int		to_pipe(t_central *central, char **split);
void	init_pipes(int pipe_fd[][2], int pipe_amm);
void	close_unused_pipes(int pipe_fd[][2], int pipe_amm, int current_index);
void	set_pipe_fds(int pipe_fd[][2], int pipe_amm, int current_index);
void	close_all_pipes(int pipe_fd[][2], int pipe_amm);

// redir_utils //
void	reset_fds(int status);

// utils //
void	has_shell_operator(t_central *central, char **split);
int		ft_strcmp(char *s1, char *s2);

//--------------------------------------------------------------//

#endif
