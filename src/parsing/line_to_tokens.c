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

static int	get_tokens(t_vector *p_tokens, char *line);
static void	get_line(char **p_line, int *p_ret);

/* to check
 *	-> get_line fail (with ret) : DONE ;
 *	-> get_tokens fail : TO DO ;
*/
int	line_to_tokens(t_minishell *p_mini, t_vector *p_tokens)
{
	char	*line;
	int		ret;

	get_line(&line, &ret);
	if (ret != 0)
		return (ret);
	if (g_my_signal != 0)
		return (0);
	if (line == NULL)
	{
		p_mini->should_exit = TRUE;
		return (1);
	}
	if (line && *line)
		add_history(line);
	return (get_tokens(p_tokens, line));
}

/* to check
 *	-> *p_line = NULL and *p_ret != 0 : DONE -> OK !
 *	-> readline = NULL : DONE -> OK !
*/
static void	get_line(char **p_line, int *p_ret)
{
	*p_ret = 0;
	if (isatty(0) == 1)
	{
		*p_line = readline("prompt >> ");
		if (g_my_signal != 0)
		{
			return ;
		}
	}
	else
	{
		*p_line = get_next_line(0, p_ret);
		return ;
	}
}

/* to check
 *	-> lexer fail : TO DO ;
*/
static int	get_tokens(t_vector *p_tokens, char *line)
{
	int	ret;

	ret = lexer(line, p_tokens);
	free(line);
	return (ret);
}
