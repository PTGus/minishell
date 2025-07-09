/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handling.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:36:40 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/09 13:52:16 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_HANDLING_H
# define ERR_HANDLING_H

// ERR_HANDLING //

// errors //
void	bad_export(char *str);
void	bad_doc(char *str);
void	no_perms(char *str);
void	comm_not_found(char *str);
void	not_cd_dir(char *str);
void	event_not_found(char *str);
void	bad_redir_token(char *str);
void	no_home(void);
void	excessive_args(char *str);
void	not_dir(char *str);
void	is_dir(char *str);
void	no_oldpwd(void);

#endif
