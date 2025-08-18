/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:58:31 by jweber            #+#    #+#             */
/*   Updated: 2025/08/06 10:35:15 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_vectors.h"
#include "parsing.h"
#include "handle_signal.h"
#include "ft_input.h"
#include "ft_string.h"
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

static int	say_exit_return(t_minishell *p_mini);
static void	remove_newline_char(char *line);
static void	case_error_quotes(t_minishell *p_mini);
static void	init_args(char **p_args);

/* This fuction will readline with getline function
 * Then parse this line to transform it to tokens 
 * (in which p_tokens->data is a char ** containing the differents
 * tokens)
 * then it will free the line read.
 * to check
 *	-> get_line fail (with ret) : DONE -> OK !
 *	-> ft_split_args fail : DONE -> OK !
*/
int	line_to_tokens(t_minishell *p_mini, t_vector *p_tokens)
{
	char	*line;
	int		ret;
	char	*args[11];
	char	*prompt;

	prompt = get_prompt(p_mini);
	if (prompt == NULL)
		return (ERROR_MALLOC);
	get_line(p_mini, &line, &ret, prompt);
	free(prompt);
	if (ret != 0 || g_my_signal != 0)
		return (ret);
	if (line == NULL)
		return (say_exit_return(p_mini));
	else
		remove_newline_char(line);
	if (line && *line && isatty(0) == 1)
		add_history(line);
	init_args(args);
	ret = ft_split_args(p_tokens, line, args);
	if (ret == ERROR_UNCLOSED_D_QUOTES || ret == ERROR_UNCLOSED_S_QUOTES)
		case_error_quotes(p_mini);
	free(line);
	return (ret);
}

static int	say_exit_return(t_minishell *p_mini)
{
	p_mini->should_exit = TRUE;
	return (0);
}

static void	remove_newline_char(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0)
	{
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
	}
}

static void	init_args(char **p_args)
{
	p_args[0] = "&&";
	p_args[1] = "||";
	p_args[2] = "<<";
	p_args[3] = ">>";
	p_args[4] = ">";
	p_args[5] = "<";
	p_args[6] = "|";
	p_args[7] = "(";
	p_args[8] = ")";
	p_args[9] = ";";
	p_args[10] = NULL;
}

static void	case_error_quotes(t_minishell *p_mini)
{
	p_mini->last_error_code = 2;
	p_mini->is_error_syntax = TRUE;
}
