/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:32:40 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/21 15:34:34 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_UP_H
# define CLEAN_UP_H

# include "../../includes/types.h"

// CLEAN_UP //

// free/2 //
void	clean_doc(char *line);
void	clean_all(t_central *central);
void	ft_envfreeone(t_envp *dupenv);
void	free_env(t_envp **dupenv);
void	ft_freesplit(char **split);
void	free_input_list(t_input *head);
void	free_central_cmd(t_central *central);
void	post_loop_cleanup(t_central *central, char *rl);
void	free_heredoc_paths(t_central *central);

#endif
