/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:34:04 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/21 15:34:34 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "../../includes/types.h"

// COMMANDS //

// executer //
int		commander(t_central *central, t_input *cmd);
void	executer(char *exec, t_central *central, t_input *cmd);
char	*pather(t_envp *path, char *cmd);

#endif
