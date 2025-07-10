/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:42:20 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/10 15:26:28 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

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
	char			***heredoc_paths;
	int				curr_cmd_idx;
	int				curr_heredoc_idx;
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

# include "../srcs/built_in/built_in.h"
# include "../srcs/clean_up/clean_up.h"
# include "../srcs/commands/commands.h"
# include "../srcs/err_handling/err_handling.h"
# include "../srcs/main/main.h"
# include "../srcs/parsing/parsing.h"
# include "../srcs/pipes/pipes.h"
# include "../srcs/redirections/redirections.h"
# include "../srcs/signals/signals.h"
# include "../srcs/utils/utils.h"

#endif
