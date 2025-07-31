/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:52:09 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/31 12:41:15 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../../includes/types.h"

// UTILS //

// cd_utils //
void	cd_oldpwd(t_central *central);
void	cd_to_home(t_central *central);
void	set_bpwd(t_envp **dupenv, int count);
void	set_back(t_envp **pwd);

// central_utils //
void	init_central(t_central *centralnv);

// env_utils\2 //
void	organise_env(t_envp **dupenv);
void	reorder_dupenv(t_envp **dupenv);
void	env_delone(t_envp *to_del);
void	insert_before_last(t_envp **dupenv, t_envp *curr);
t_envp	*ft_getenv(t_envp **dupenv, char *to_find);
void	init_empty_env(t_envp **dupenv);
char	*segment_env(char *envp, int idx);

// exec_utils\2 //
char	*get_line(t_envp *dupenv);
char	**get_exec_env(t_envp **dupenv);
int		is_relative(char *cmd);
void	do_solo(t_central *central, t_input *cmd);
int		is_built_in(t_input *cmd);
int		is_cmd_valid(char *cmd);
char	**get_exec_flags(t_input *cmd);
int		do_absolute(t_central *central, t_input *cmd);

// exit_utils //
int		is_all_signs(char *str);
int		is_under_min(char *val);
int		is_over_max(char *val);

// export utils //
int		is_special_exportion(t_central *central, char *exportion);
void	print_declaration(t_envp *curr);
void	hidden_export(t_central *central, char *exportion, int has_equal);
t_envp	*new_valuesless_env(char *envp);
int		to_pipe(t_central *central);
int		validity_check(char *str);
void	trunc_export(t_envp *var, char *exportion, int index);

// gnl //
char	*get_next_line(int fd);
void	ft_free(char **ptr);
char	*set_line(char *str);
char	*fill_line(int fd, char *nxt, char *buf);

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
int		check_for_bad_redir(char *cmd);
void	reset_fds(int status);
int		has_heredocs(t_central *central);

// rl_utils //
int		is_space_tab(char *str);

// utils //
t_input	*find_cmd(t_input *cmd);
void	has_shell_operator(t_central *central, char *rl);
int		ft_strcmp(char *s1, char *s2);
void	increase_shlvl(t_envp **dupenv);

#endif
