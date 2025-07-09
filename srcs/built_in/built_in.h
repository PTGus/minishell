/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:26:30 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/09 14:04:44 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

// BUILT-IN //

// cd //
void	ft_cd(t_central *central, t_input *cmd);
void	set_cd_values(t_envp **dupenv, t_input *cmd);
void	set_home(t_envp **dupenv);
void	set_pwd(t_envp **dupenv);
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
void	ft_unset(t_central *central, t_input *cmd);

#endif
