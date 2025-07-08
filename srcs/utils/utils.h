/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:52:09 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/08 16:20:16 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

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

// exec_utils\2 //
char	*get_line(t_envp *dupenv);
char	**get_exec_env(t_envp **dupenv);
int		is_relative(char *cmd);
void	do_solo(t_central *central, t_input *cmd);
int		is_built_in(t_input *cmd);
int		is_cmd_valid(char *cmd);

// export utils //
int		is_special_exportion(t_central *central, char *exportion);
void	print_declaration(t_envp *curr);
void	hidden_export(t_central *central, char *exportion, int has_equal);
t_envp	*new_valuesless_env(char *envp);
int		to_pipe(t_central *central);
int		validity_check(char *str);

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


#endif
