/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:47:58 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/10 15:49:17 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

// REDIRECTIONS //

// append_redir //
int		append_redir(t_input *cmd);

// heredoc //
int		redirect_doc_path(char **path);
int		ft_heredoc(t_central *central, char *delimiter, int doc_type);

// input_redir //
int		set_input(t_input *cmd);

// output_redir //
int		set_output(t_input *cmd);

// redirect //
int		handle_all_heredocs(t_central *central);
int		has_to_redirect(t_central *central, t_input *cmd);

#endif
