/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:24:04 by jweber            #+#    #+#             */
/*   Updated: 2025/07/02 16:44:25 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_vectors.h"
#include "parsing.h"
#include "printing.h"
#include "ft_io.h"
#include <readline/readline.h>
#include <readline/history.h>

static int	check_errors(t_minishell *p_mini, t_vector *p_tokens);
static int	line_to_tokens(t_minishell *p_mini, t_vector *p_tokens);
static int	get_tokens(t_minishell *p_mini, t_vector *p_tokens, char **p_line);

int	tokenize(t_minishell *p_mini, t_vector *p_tokens)
{
	int		ret;

	ret = line_to_tokens(p_mini, p_tokens);
	if (ret != 0)
	{
		// do other stuff ?
		return (ret);
	}
	ret = check_errors(p_mini, p_tokens);
	if (ret != 0)
	{
		// do stuff 
		// return ;
	}
	return (0);
}

static int	line_to_tokens(t_minishell *p_mini, t_vector *p_tokens)
{
	char	*line;
	int		ret;

	line = readline("prompt >> ");
	if (line == NULL)
	{
		p_mini->should_exit = TRUE;
		return (1);
	}
	if (line && *line)
		add_history(line);
	ret = check_parenthesis(line);
	if (ret != 0)
	{
		free(line);
		print_error(ret);
		return (1);
	}
	ret = get_tokens(p_mini, p_tokens, &line);
	if (ret != 0)
	{
		return (ret);
	}
	return (0);
}

static int	get_tokens(t_minishell *p_mini, t_vector *p_tokens, char **p_line)
{
	int	ret;

	ret = lexer(*p_line, p_tokens);
	if (ret != 0)
	{
		if (ret > 0)
		{
			free(*p_line);
			print_error(ret);
			p_mini->last_error_code = 2;
			return (1);
		}
		else
		{
			// do stuff ?
			free(*p_line);
			return (ret);
		}
	}
	free(*p_line);
	return (0);
}

static int	check_errors(t_minishell *p_mini, t_vector *p_tokens)
{
	int	ret;

	ret = check_error_syntax(*p_tokens);
	if (ret != 0)
	{
		ft_putstr_fd("error syntax in check_error_syntax !\n", 2);
		return (0);
	}
	if (p_tokens->size <= 0)
	{
		ft_putstr_fd("token.size == 0 -> continue and wait next input !\n", 2);
		ft_vector_free(p_tokens);
		return (0);
	}
	ret = prepare_here_doc(p_mini, p_tokens);
	if (ret != 0)
	{
		// do stuff 
	}
	return (0);
}
