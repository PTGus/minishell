/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:42:20 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/23 12:27:06 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L
# define _XOPEN_SOURCE 600
# define _GNU_SOURCE

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
# include <limits.h>
# include "types.h"
# include "../libft/libft.h"
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

extern int	g_signal;

#endif
