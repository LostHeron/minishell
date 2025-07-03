/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:19:57 by jweber            #+#    #+#             */
/*   Updated: 2025/05/16 09:22:08 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "ft_string.h"
#include "ft_io.h"
#include <stdio.h>
#include <sys/types.h>

static ssize_t	get_bloc_size(char *line, int *p_err_code);
static ssize_t	get_end(char *line, char c);
//static ssize_t	get_word_size(char *line, char **args);

char	*get_next_token(char **p_line, char **args, int *p_err_code)
{
	ssize_t	token_size;
	char	*token;
	ssize_t	len_strstr;
	ssize_t	quote_size;

	len_strstr = ft_strstr_args(*p_line, args);
	if (len_strstr != 0)
		token_size = len_strstr;
	else
	{
		token_size = 0;
		while ((*p_line)[token_size] != '\0' && \
					ft_strchr(WHITE_SPACES, (*p_line)[token_size]) == NULL && \
					ft_strstr_args((*p_line) + token_size, args) == 0)
		{
			if (ft_strchr("\"'", (*p_line)[token_size]) != NULL)
			{
				quote_size = get_bloc_size((*p_line) + token_size, p_err_code);
				if (quote_size < 0)
				{
					return (NULL);
				}
				token_size += quote_size;
			}
			else
				token_size++;
		}
	}
	/*
	if (ft_strchr("\"('", (*p_line)[0]) != NULL)
		token_size = get_bloc_size(*p_line, p_err_code);
	else if (len_strstr != 0)
		token_size = len_strstr;
	else
		token_size = get_word_size(*p_line, args);
	*/
	/*
	if (token_size < 0)
	{
		return (NULL);
	}
	*/
	if (token_size > 0)
	{
		token = ft_strndup(*p_line, token_size);
		if (token == NULL)
		{
			*p_err_code = ERROR_MALLOC;
			return (NULL);
		}
		*p_line += token_size;
		return (token);
	}
	else if (token_size == 0)
	{
		return (NULL);
	}
	else
	{
		ft_putstr_fd("get_next_token error : should not get to token_size < 0\n", 2);
		exit(1);
	}
}

/*
static ssize_t	get_word_size(char *line, char **args)
{
	size_t	i;

	i = 0;
	while (line[i] && ft_strchr(WHITE_SPACES, line[i]) == NULL \
					&& ft_strstr_args(line + i, args) == 0 \
					&& ft_strchr("\"('", line[i]) == NULL)
		i++;
	return (i);
}
*/

static ssize_t	get_bloc_size(char *line, int *p_err_code)
{
	ssize_t	i;
	char	type;

	i = 0;
	type = line[i];
	if (line[i] == '\"')
		i = get_end(line + 1, '\"');
	else if (line[i] == '\'')
		i = get_end(line + 1, '\'');
	else
	{
		ft_putstr_fd("ERROR in function 'get_bloc_size', \
						should never get here !\n", 2);
	}
	if (i < 0)
	{
		if (type == '\"')
			*p_err_code = ERROR_UNCLOSED_D_QUOTES;
		else
			*p_err_code = ERROR_UNCLOSED_S_QUOTES;
		return (i);
	}
	else
		return (i + 1);
}

static ssize_t	get_end(char *line, char c)
{
	ssize_t	i;

	i = 0;
	while (line[i] && line[i] != c)
		i++;
	if (line[i] == '\0')
		return (-1);
	else
		return (i + 1);
}
