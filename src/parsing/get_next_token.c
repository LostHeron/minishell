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
#include <stdio.h>
#include <sys/types.h>

static int		case_not_an_args(ssize_t *p_token_size,
					char **p_line, char **args);
static int		dup_new_token(char **p_token_i, char **p_line,
					size_t token_size);
static ssize_t	get_bloc_size(char *line, int *p_err_code);
static ssize_t	get_end(char *line, char c);

/* to check
 *	-> case_not_an_args fail : DONE -> OK !
 *	-> dup_new_token fail : DONE -> OK !
*/
int	get_next_token(char **p_token_i, char **p_line, char **args)
{
	ssize_t	token_size;
	ssize_t	len_strstr;
	int		ret;

	*p_token_i = NULL;
	len_strstr = ft_strstr_args(*p_line, args);
	if (len_strstr != 0)
		token_size = len_strstr;
	else
	{
		ret = case_not_an_args(&token_size, p_line, args);
		if (ret != 0)
			return (ret);
	}
	ret = dup_new_token(p_token_i, p_line, token_size);
	if (ret != 0)
		return (ret);
	return (0);
}

/* to check
 *	-> get_block_size return ERROR : DONE -> OK !
*/
static int	case_not_an_args(ssize_t *p_token_size,
					char **p_line, char **args)
{
	ssize_t	quote_size;
	int		err_code;

	(*p_token_size) = 0;
	while ((*p_line)[(*p_token_size)] != '\0'
				&& ft_strchr(WHITE_SPACES, (*p_line)[(*p_token_size)]) == NULL
				&& ft_strstr_args((*p_line) + (*p_token_size), args) == 0)
	{
		if (ft_strchr("\"'", (*p_line)[(*p_token_size)]) != NULL)
		{
			quote_size = get_bloc_size((*p_line) + (*p_token_size), &err_code);
			if (err_code != 0)
				return (err_code);
			(*p_token_size) += quote_size;
		}
		else
			(*p_token_size)++;
	}
	return (0);
}

/* to check
 *	-> ft_strndup fail : DONE -> OK !
*/
static int	dup_new_token(char **p_token_i, char **p_line, size_t token_size)
{
	if (token_size > 0)
	{
		*p_token_i = ft_strndup(*p_line, token_size);
		if (*p_token_i == NULL)
		{
			return (ERROR_MALLOC);
		}
		*p_line += token_size;
		return (0);
	}
	else
		return (0);
}

/* to check
 *	nothing, this function only return
 *	a value different than 0 if the closure of " or ' is 
 *	not found until end of line 
*/
static ssize_t	get_bloc_size(char *line, int *p_err_code)
{
	ssize_t	i;
	char	type;

	*p_err_code = 0;
	i = 0;
	type = line[i];
	if (line[i] == '\"')
		i = get_end(line + 1, '\"');
	else if (line[i] == '\'')
		i = get_end(line + 1, '\'');
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

/*
 * nothing to check;
 * only return -1 is the closure of che char c (" or ') is not found
*/
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
