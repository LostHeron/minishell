/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:58:31 by jweber            #+#    #+#             */
/*   Updated: 2025/07/18 11:05:17 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_vectors.h"
#include "parsing.h"
#include "printing.h"
#include "ft_io.h"
#include "handle_signal.h"
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

static int	get_tokens(t_minishell *p_mini, t_vector *p_tokens, char *line);

int	line_to_tokens(t_minishell *p_mini, t_vector *p_tokens)
{
	char	*line;
	int		ret;

	if (isatty(0) == 1)
	{
		line = readline("prompt >> ");
		if (my_signal != 0)
		{
			rl_replace_line("\0", 0);
		}
	}
	else
	{
		line = get_next_line(0, &ret);
		if (ret != 0)
			return (ret);
	}
	if (line == NULL)
	{
		p_mini->should_exit = TRUE;
		return (1);
	}
	if (line && *line)
		add_history(line);
	ret = get_tokens(p_mini, p_tokens, line);
	if (ret != 0)
	{
		return (ret);
	}
	return (0);
}

static int	get_tokens(t_minishell *p_mini, t_vector *p_tokens, char *line)
{
	int	ret;

	ret = lexer(line, p_tokens);
	if (ret != 0)
	{
		if (ret > 0)
		{
			free(line);
			print_error(ret);
			p_mini->last_error_code = 2;
			return (ret);
		}
		else
		{
			free(line);
			p_mini->last_error_code = 2;
			return (ret);
		}
	}
	free(line);
	return (0);
}
