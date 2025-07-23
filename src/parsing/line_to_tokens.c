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
#include "ft_io.h"
#include "handle_signal.h"
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	get_line(char **p_line, int *p_ret);
static void	init_args(char **p_args);

/* to check
 *	-> get_line fail (with ret) : DONE -> OK !
 *	-> ft_split_args fail : DONE -> OK !
*/
int	line_to_tokens(t_minishell *p_mini, t_vector *p_tokens)
{
	char	*line;
	int		ret;
	char	*args[11];

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
	init_args(args);
	ret = ft_split_args(p_tokens, line, args);
	free(line);
	return (ret);
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

static void	init_args(char **p_args)
{
	p_args[10] = NULL;
	p_args[0] = "&&";
	p_args[1] = "||";
	p_args[2] = "<<";
	p_args[3] = ">>";
	p_args[4] = "|";
	p_args[5] = "&";
	p_args[6] = ">";
	p_args[7] = "<";
	p_args[8] = "(";
	p_args[9] = ")";
}
