/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:46:46 by jweber            #+#    #+#             */
/*   Updated: 2025/05/14 18:12:15 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_single_quotes(char *line, int *p_i, int *p_word_i, int *p_err_code)
{
	if (line[*p_i] == '\'')
	{
		(*p_i)++;
		while (line[*p_i] && line[*p_i] != '\'')
			p_i++;
		if (line[*p_i] == '\0')
		{
			*p_err_code = ERROR_UNCLOSED_S_QUOTES;
			return (-1);
		}
		else
		{
			(*p_word_i)++;
			(*p_i)++;
		}
	}
	return (0);
}

int	handle_double_quotes(char *line, int *p_i, int *p_word_i, int *p_err_code)
{
	if (line[*p_i] == '\"')
	{
		(*p_i)++;
		while (line[*p_i] && line[*p_i] != '\"')
			(*p_i)++;
		if (line[*p_i] == '\0')
		{
			*p_err_code = ERROR_UNCLOSED_D_QUOTES;
			return (-1);
		}
		else
		{
			(*p_word_i)++;
			(*p_i)++;
		}
	}
	return (0);
}

int	handle_parenthesis(char *line, int *p_i, int *p_word_i, int *p_err_code)
{
	if (line[*p_i] == '(')
	{
		(*p_i)++;
		while (line[*p_i] && line[*p_i] != ')')
			(*p_i)++;
		if (line[*p_i] == '\0')
		{
			*p_err_code = ERROR_UNCLOSED_PARENTHESIS;
			return (-1);
		}
		else
		{
			(*p_word_i)++;
			(*p_i)++;
		}
	}
	return (0);
}
