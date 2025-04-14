/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:42:20 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/14 17:11:24 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
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
}	t_envp;

//--------------------------------------------------------------//

int		main(int ac, char **av, char **env);
void	do_cmd(char **split, t_envp **dupenv);
void	handle_signals(void);

//--------------------------------------------------------------//

// UTILS //
int		ft_strcmp(char *s1, char *s2);
void	ft_free_split(char **str);
char	*pather(char *cmd);

// lst_utils //
void	ft_lst_back(t_envp **dupenv, t_envp *curr);
t_envp	*lstlast(t_envp *dupenv);

//--------------------------------------------------------------//

// BUILT-IN //

// cd //
void	ft_cd(char **split, t_envp **dupenv);
void	set_pwd(t_envp **dupenv, char *path);
void	set_old_pwd(t_envp **dupenv);

// echo //
void	ft_echo(char **split);

// env //
void	ft_env(t_envp **dupenv);
t_envp	*new_env(char *envp);
int		init_env(t_envp **dupenv, char **envp);
int 	duplicate_env(t_envp **dupenv, char **envp);

// export //
void	ft_export(char **split, t_envp **dupenv);

// pwd //
void	ft_pwd(void);

//--------------------------------------------------------------//

#endif