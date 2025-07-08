/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:34:04 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/08 10:49:36 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

// COMMANDS //

// executer //
int		commander(t_central *central, t_input *cmd);
void	executer(char *exec, t_central *central, t_input *cmd);
char	*pather(t_envp *path, char *cmd);


#endif
