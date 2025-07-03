/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:42:20 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/03 14:06:00 by gumendes         ###   ########.fr       */
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
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <errno.h>
# include "../libft/libft.h"

extern int	g_signal;

# define _POSIX_C_SOURCE 200809L

# define ARGUMENT	0
# define REDIR_IN	1
# define REDIR_OUT	2
# define APPEND_OUT	3
# define HERE_DOC	4
# define HERE_DOC_Q	5

# define UNQUOTED	0
# define SINGLE_Q	1
# define DOUBLE_Q	2

typedef struct s_input
{
	struct s_input	*next;
	struct s_input	*prev;
	int				index;
	char			*value;
	int				token;
}	t_input;

typedef struct s_central
{
	struct s_envp	*dupenv;
	int				exit_val;
	struct s_input	**cmd;
	char			**pipe_matrix;
	int				matrix_len;
	int				curr_cmd;
	int				has_exited;
}	t_central;

typedef struct s_envp
{
	struct s_envp	*next;
	struct s_envp	*prev;
	char			*var;
	char			*value;
	int				index;
	int				visible_env;
	int				has_equal;
}	t_envp;

//--------------------------------------------------------------//

// BUILT-IN //

// cd //
void	ft_cd(t_central *central, t_input *cmd);
void	set_cd_values(t_envp **dupenv, t_input *cmd);
void	set_home(t_envp **dupenv);
void	set_pwd(t_envp **dupenv, char *path);
void	set_old_pwd(t_envp **dupenv);

// echo //
void	ft_echo(t_central *central, t_input *cmd);
void	do_echo(t_input *cmd);
void	echo_n(t_input *cmd);

// env //
void	ft_env(t_central *central, t_input *cmd);
t_envp	*new_env(char *envp);
int		init_env(t_envp **dupenv, char **envp);
int		duplicate_env(t_envp **dupenv, char **envp);

// exit //
void	ft_exit(t_central *central, t_input *cmd);

// export //
int		should_revalue(t_envp **dupenv, char *exportion);
void	declarex(t_envp **dupenv);
void	ft_export(t_central *central, t_input *cmd);

// pwd //
void	ft_pwd(t_central *central);

// unset //
void	ft_unset(t_central *central, char *to_unset);

//--------------------------------------------------------------//

// CLEAN_UP //

// free/2 //
void	clean_doc(char *rl_doc, char *tmp);
void	clean_all(t_central *central);
void	ft_envfreeone(t_envp *dupenv);
void	free_env(t_envp *dupenv);
void	ft_freesplit(char **split);
void	free_input_list(t_input *head);
void	free_central_cmd(t_central *central);
void	post_loop_cleanup(t_central *central, char *rl);

//--------------------------------------------------------------//

// COMMANDS //

// executer //
int		commander(t_central *central, t_input *cmd);
void	executer(char *exec, t_central *central, t_input *cmd);
char	*pather(t_envp *path, char *cmd);

//--------------------------------------------------------------//

// ERR_HANDLING //

// errors //
void	bad_export(char *str);
void	bad_doc(char *str);
void	no_perms(char *str);
void	comm_not_found(char *str);
void	not_dir(char *str);
void	event_not_found(char *str);
void	bad_redir_token(char *str);
void	no_home(void);

//--------------------------------------------------------------//

// MAIN //

// minishell //
int		main(int ac, char **av, char **env);
void	do_cmd(t_central *central, t_input *cmd);
void	rl_loop(t_central *central);
int		do_builtin(t_central *central, t_input *cmd);

//--------------------------------------------------------------//

// PIPES //

// pipe //
void	execute_pipes(t_central *central, t_input *cmd, \
			int (*pipe_fd)[2], int curr_index);
void	piper(t_central *central);

//--------------------------------------------------------------//

// REDIRECTIONS //

// append_redir //
int		append_redir(t_input *cmd);

// heredoc //
int		ft_heredoc(t_central *central, char *delimiter, int doc_type);
void	redirect_to_doc(int fd);

// input_redir //
int		set_input(t_input *cmd);

// output_redir //
int		set_output(t_input *cmd);

// redirect //
int		has_to_redirect(t_central *central, t_input *cmd);
int		set_redirections(t_central *central, t_input *cmd);
int		do_redirection(t_central *central, t_input *cmd);

//--------------------------------------------------------------//
// SIGNALS //

// heredoc_signals //
void	setup_heredoc_signals(void);

// signals //
void	ctrl_c(int sig);
void	ctrl_d(void);
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
t_envp	*ft_getenv(t_envp **dupenv, char *to_find);

// exec_utils //
char	*get_line(t_envp *dupenv);
char	**get_exec_env(t_envp **dupenv);
int		is_relative(char *cmd);
void	do_solo(t_central *central, t_input *cmd);

// export utils //
int		is_special_exportion(t_central *central, char *exportion);
void	print_declaration(t_envp *curr);
void	hidden_export(t_central *central, char *exportion, int has_equal);
t_envp	*new_valuesless_env(char *envp);
int		to_pipe(t_central *central);

// list_utils //
void	ft_lst_back(t_envp **dupenv, t_envp *curr);
t_envp	*lstlast(t_envp **dupenv);

// pipe_utils //
int		to_pipe(t_central *central);
void	init_pipes(int (*pipe_fd)[2], int pipe_amm);
void	close_unused_pipes(int (*pipe_fd)[2], int pipe_amm, int current_index);
void	set_pipe_fds(int (*pipe_fd)[2], int pipe_amm, int current_index);
void	close_all_pipes(int (*pipe_fd)[2], int pipe_amm);

// redir_utils //
int		check_for_bad_redir(char *to_redir);
void	reset_fds(int status);

// utils //
char	**get_exec_flags(t_input *cmd);
t_input	*find_cmd(t_input *cmd);
void	has_shell_operator(t_central *central);
int		ft_strcmp(char *s1, char *s2);
void	increase_shlvl(t_envp **dupenv);
int		is_built_in(t_input *cmd);

//--------------------------------------------------------------//

// PARSE //

// expand_docs //
char	*ft_check_expand_doc(t_central *central, char *str);
int		ft_get_expand_doc(char *str, int j);
char	*ft_assign_expand_doc(char **str, int *vals,
			char *new_str, char *expand);
char	*ft_execute_expand_doc(t_central *central, char **str,
			int start, int end);

// expand_utils //
char	*ft_get_dupenv_val(t_central *central, char *str);
int		ft_is_node_spaced(t_input *node);
void	ft_insert_split_node(t_input *first, t_input *second);

// expander //
int		ft_expander(t_central *central);
int		ft_check_expand(t_central *central, t_input *node);
int		ft_get_expand_end(char *str, int j);
void	ft_assign_expand(char **str, int *vals, char *new_str, char *expand);
int		ft_execute_expand(t_central *central, char **str, int start, int end);

// frees //
void	ft_free_split(char **split);
void	ft_free_list_err(t_central *central, char *str, t_input *current);
void	ft_free_strings(char *temp, char *expand);

// input_utils //
t_input	*ft_input_new(void *value, int index);
t_input	*ft_input_last(t_input *lst);
void	ft_input_add_back(t_input **lst, t_input *new_node);
int		ft_input_size(t_input *lst);
void	ft_input_iter(t_input *lst, void (*f)(void *));

// parsing //
int		ft_parse(char *prompt, t_central *central);
void	ft_init_parse(t_central *central);
void	ft_error(char *message);

// print_utils //
void	ft_print_arr(char **str_arr);
void	ft_print_list_array(t_input **array);

// quotes //
int		ft_is_quoted(char *prompt, int end_pos);
void	ft_quote_eraser(t_central *central);
int		ft_quote_checker(t_input *node);
int		ft_erase_node_quotes(t_input *node, int count);

// redirects //
int		ft_space_redirects(t_central *central);
int		ft_are_redirects_invalid(t_central *central);
int		ft_redirect_check(char *str, int j);
int		ft_count_unspaced_redirects(char *str, int j, int extra_space);
char	*ft_realloc_redir_str(char *str, int to_space);

// spacing //
int		ft_remove_extra_spaces(t_central *central);
int		ft_new_spaced_len(char *command);
void	ft_assign_new_split(char **new_split, char **matrix, int i);
int		ft_rest_is_space(char *str, int j);

// split //
char	**ft_split_pipes(char *prompt, t_central *central);
int		ft_pipe_count(char *prompt);
char	**ft_handle_split(char *prompt, char **split);

// tokenizer //
int		ft_tokenizer(t_central *central);
int		ft_make_list(t_central *central);
int		ft_assign_list(t_central *central, int i, int l, int index);
int		ft_assign_token(t_input *node);
int		ft_is_delimiter_quoted(t_input *current);

#endif
