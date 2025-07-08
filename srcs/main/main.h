/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:38:04 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/08 10:49:36 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

// MAIN //

// minishell //
int		main(int ac, char **av, char **env);
void	do_cmd(t_central *central, t_input *cmd);
void	rl_loop(t_central *central);
int		do_builtin(t_central *central, t_input *cmd);

#endif