/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:42:20 by gumendes          #+#    #+#             */
/*   Updated: 2025/05/09 15:32:39 by gumendes         ###   ########.fr       */
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

# define COMMAND	0
# define CMD_FLAGS	1
# define REDIR_IN	2
# define REDIR_OUT	3
# define APPEND_IN	4
# define APPEND_OUT	5
# define ARGUMENT	6

typedef struct s_central
{
	struct s_envp	*dupenv;
	int				exit_val;
	struct s_input	**command_list;
}	t_central;

typedef struct s_envp
{
	struct s_envp	*next;
	struct s_envp	*prev;
	char			*var;
	char			*value;
	int				index;
}	t_envp;

typedef struct s_input
{
	struct s_input	*next;
	struct s_input	*prev;
	char			*value;
	int				index;
	int				token_type;
}	t_input;

//--------------------------------------------------------------//

// BUILT-IN //

// cd //
void	ft_cd(char **split, t_central *central);
void	set_cd_values(t_envp **dupenv, char **split);
void	set_pwd(t_envp **dupenv, char *path);
void	set_old_pwd(t_envp **dupenv);
void	set_home(t_envp **dupenv);

// echo //
void	ft_echo(char **split, t_central *central);

// env //
void	ft_env(char **split, t_central *central);
t_envp	*new_env(char *envp);
int		init_env(t_envp **dupenv, char **envp);
int		duplicate_env(t_envp **dupenv, char **envp);

// exit //
void	ft_exit(t_central *central, char *exit_val);

// export //
void	ft_export(char **split, t_central *central);
int		should_revalue(t_envp **dupenv, char**split);
void	insert_before_last(t_envp **dupenv, t_envp *curr);

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
void	executer(char *exec, char **split, t_central *central);
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
void	do_cmd(char **split, t_central *central);
void	rl_loop(t_central *central);
int		is_built_in(t_central *central, char **split);

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

// exec_utils //
char	*get_line(t_envp *dupenv);
char	**get_exec_env(t_envp **dupenv);

// lst_utils //
void	ft_lst_back(t_envp **dupenv, t_envp *curr);
t_envp	*lstlast(t_envp **dupenv);

// utils //
int		ft_strcmp(char *s1, char *s2);

//--------------------------------------------------------------//

// PARSE //

// parsing //
int		ft_parse(char *prompt);
int		ft_is_quoted(char *prompt, int end_pos);
void	ft_error(char *message);
void	ft_tokenize(char *prompt);

// split //
char	**ft_split_pipes(char *prompt);
int		ft_pipe_count(char *prompt);
char	**ft_handle_split(char *prompt, char **split);
void	ft_print_arr(char **str_arr);
void	ft_free_split(char **split);

// spacing //
char	**ft_remove_extra_spaces(char **split);
int		ft_spaced_len(char *command);
int		ft_is_space(int c);

#endif
