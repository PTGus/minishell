/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:42:20 by gumendes          #+#    #+#             */
/*   Updated: 2025/04/09 17:16:10 by gumendes         ###   ########.fr       */
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
void	handle_signals(void);

//--------------------------------------------------------------//

// UTILS //
int		ft_strcmp(char *s1, char *s2);
void	ft_free_split(char **str);
char	*pather(char *cmd);
int 	duplicate_env(t_envp **dupenv, char **envp);

// lst_utils //
int		init_env(t_envp **dupenv, int count);
int		populate_env(t_envp **dupenv, char **envp);

//--------------------------------------------------------------//

// BUILT-IN //

// cd //
void	ft_cd(char **split, char *home_path);

// echo //
void	ft_echo(char **split);

// env //
void	ft_env(char **env);

// pwd //
void	ft_pwd(void);

//--------------------------------------------------------------//

#endif