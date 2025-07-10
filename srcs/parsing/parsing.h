/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:39:57 by gumendes          #+#    #+#             */
/*   Updated: 2025/07/08 10:49:36 by gumendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// PARSING //

// expand_docs //
char	*ft_check_expand_doc(t_central *central, char *str);
int		ft_get_expand_doc(char *str, int j);
char	*ft_assign_expand_doc(char **str, int *vals,
			char *new_str, char *expand);
char	*ft_execute_expand_doc(t_central *central, char **str,
			int start, int end);

// expand_utils //
char	*ft_get_dupenv_val(t_central *central, char *str);
int		ft_is_node_spaced(t_input *node);
void	ft_insert_split_node(t_input *first, t_input *second);
void	ft_mark_empty_expand(t_input *node);

// expander //
int		ft_expander(t_central *central);
int		ft_check_expand(t_central *central, t_input *node);
int		ft_get_expand_end(char *str, int j);
void	ft_assign_expand(char **str, int *vals, char *new_str, char *expand);
int		ft_execute_expand(t_central *central, char **str, int start, int end);

// frees //
void	ft_free_split(char **split);
void	ft_free_list_err(t_central *central, char *str, t_input *current);
void	ft_free_strings(char *temp, char *expand);

// input_utils //
t_input	*ft_input_new(void *value, int index);
t_input	*ft_input_last(t_input *lst);
void	ft_input_add_back(t_input **lst, t_input *new_node);
int		ft_input_size(t_input *lst);
void	ft_input_iter(t_input *lst, void (*f)(void *));

// parsing //
int		ft_parse(char *prompt, t_central *central);
void	ft_init_parse(t_central *central);
void	ft_error(char *message);

// print_utils //
void	ft_print_arr(char **str_arr);
void	ft_print_list_array(t_input **array);

// quotes //
int		ft_is_quoted(char *prompt, int end_pos);
void	ft_quote_eraser(t_central *central);
int		ft_quote_checker(t_input *node);
int		ft_erase_node_quotes(t_input *node, int count);

// redirects //
int		ft_space_redirects(t_central *central);
int		ft_are_redirects_invalid(t_central *central);
int		ft_redirect_check(char *str, int j);
int		ft_count_unspaced_redirects(char *str, int j, int extra_space);
char	*ft_realloc_redir_str(char *str, int to_space);

// spacing //
int		ft_remove_extra_spaces(t_central *central);
int		ft_new_spaced_len(char *command);
void	ft_assign_new_split(char **new_split, char **matrix, int i);
int		ft_rest_is_space(char *str, int j);

// split //
char	**ft_split_pipes(char *prompt, t_central *central);
int		ft_pipe_count(char *prompt);
char	**ft_handle_split(char *prompt, char **split);

// tokenizer //
int		ft_tokenizer(t_central *central);
int		ft_make_list(t_central *central);
int		ft_assign_list(t_central *central, int i, int l, int index);
int		ft_assign_token(t_input *node);
int		ft_is_delimiter_quoted(t_input *current);

#endif
