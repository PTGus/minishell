/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:47:58 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/08 10:49:59 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

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

# endif
