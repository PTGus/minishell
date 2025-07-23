/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:33:31 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/23 12:07:13 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

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
	int				curr_hdc_idx;
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

#endif
