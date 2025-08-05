/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:58:31 by jweber            #+#    #+#             */
/*   Updated: 2025/08/05 11:58:47 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "minishell.h"
#include "ft_vectors.h"
#include "parsing.h"
#include "ft_io.h"
#include "handle_signal.h"
#include "ft_input.h"
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

static void	get_line(t_minishell *p_mini, char **p_line, int *p_ret);
static void	init_args(char **p_args);
static void	restore_sigquit(void);
static void	do_nothing(int sig);

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

	get_line(p_mini, &line, &ret);
	if (ret != 0)
		return (ret);
	if (g_my_signal != 0)
		return (0);
	if (line == NULL)
	{
		p_mini->should_exit = TRUE;
		return (0);
	}
	if (line && *line)
		add_history(line);
	restore_sigquit();
	init_args(args);
	ret = ft_split_args(p_tokens, line, args);
	free(line);
	return (ret);
}

/* to check
 *	-> get_prompt_fail : DONE -> OK ;
 *	-> *p_line = NULL and *p_ret != 0 : DONE -> OK !
 *	-> readline = NULL : DONE -> OK !
*/
static void	get_line(t_minishell *p_mini, char **p_line, int *p_ret)
{
	char	*prompt;
	int		ret;

	*p_ret = 0;
	if (isatty(0) == 1)
	{
		prompt = get_prompt(p_mini);
		if (prompt == NULL)
		{
			*p_ret = ERROR_MALLOC;
			return ;
		}
		//*p_line = readline(prompt);
		ret = rl_gnl(p_line, prompt);
		free(prompt);
		if (ret != 0)
		{
			*p_ret = ret;
			return ;
		}
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

static void	restore_sigquit(void)
{
	struct sigaction	s;

	ft_bzero(&s, sizeof(struct sigaction));
	s.sa_handler = do_nothing;
	s.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &s, NULL);
}

static void	do_nothing(int sig)
{
	(void) sig;
	return ;
}

