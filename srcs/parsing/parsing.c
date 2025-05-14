/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:27:01 by david-fe          #+#    #+#             */
/*   Updated: 2025/05/06 12:18:38 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_quoted(char *prompt, int end_pos)
{
	int	i;
	int	quote_flag;
	
	i = -1;
	quote_flag = 0;
	if(end_pos == -1)
		end_pos = ft_strlen(prompt) - 1;
	while (prompt[++i] && i <= end_pos)
	{
		if (prompt[i] == '\'' && quote_flag == 0)
			quote_flag = 1;
		else if (prompt[i] == '\'' && quote_flag == 1)
			quote_flag = 0;
		else if (prompt[i] == '\"' && quote_flag == 0)	
			quote_flag = 2;
		else if (prompt[i] == '\"' && quote_flag == 2)	
			quote_flag = 0;
	}
	return(quote_flag);
}

int	ft_pipe_count(char *prompt)
{
	int	i;
	int pipe_num;

	i = 0;
	pipe_num = 0;
	while(prompt[i])
	{
		if (prompt[i] == '|' && ft_is_quoted(prompt, i) == 0)
			pipe_num++;
		i++;
	}
	printf("pnum %i\n", pipe_num);
	return(pipe_num);
}

char	**ft_handle_split(char *prompt, char **split)
{
	int		i;
	int		j;
	int		str_num;

	i = 0;
	j = 0;
	str_num = 0;
	while(prompt && prompt[i])
	{
		if (prompt[i] == '|'  && ft_is_quoted(prompt, i) == 0)
		{
			split[str_num++] = ft_substr(prompt, j, (i - j));
			j = i + 1;
		}
		else if (prompt[i + 1] == '\0' && ft_is_quoted(prompt, i) == 0)
		{
			split[str_num++] = ft_substr(prompt, j, (i - j + 1));
			j = i + 1;
		}
		i++;
	}
	return (split);
}

char	**ft_split_pipes(char *prompt)
{
	char	**split;
	int		pipe_num;

	if (prompt[0] == '|' || prompt[ft_strlen(prompt) - 1] == '|') // LEAKS, IN THE FUNCTIONS THAT SHOULD NOT HAPPEN AFTER!!!
		return(NULL); 
	pipe_num = ft_pipe_count(prompt);
	split = malloc((pipe_num + 2) * sizeof(char *));
	if (!split)
		return(NULL);
	if (pipe_num == 0)
		split[0] = ft_strdup(prompt);
	else
		ft_handle_split(prompt, split);
	split[pipe_num + 1] = NULL;
	return (split);
}

void	ft_tokenize(char *prompt)
{
	(void)prompt;
	return ;
}

void	ft_error(char *message)
{
	printf("%s ERROR!", message);
	exit(0);
}

void	ft_print_arr(char **str_arr)
{
	int i;

	i = 0;

	while (str_arr && str_arr[i])
	{
		printf("%d: %s\n", i, str_arr[i]);
		i++;
	}
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
		while (split[i])
			free(split[i++]);
	if (split)
		free(split);
}

int	ft_parse(char *prompt)
{
	//t_input	input;
	char	**pipe_split;
	
	if(!prompt)
		return (0);
	if (ft_is_quoted(prompt, -1) != 0)
		ft_error("quotes");
	pipe_split = ft_split_pipes(prompt);
	if (pipe_split == NULL)
		ft_error("pipes");
	ft_print_arr(pipe_split);
	ft_free_split(pipe_split);
	/*
	prompt = ft_spaced_prompt(prompt);
	ft_tokenize(prompt);
	*/
	return(0);
}
