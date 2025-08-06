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

#include "ft_memory.h"
#include "minishell.h"
#include "ft_vectors.h"
#include "parsing.h"
#include "handle_signal.h"
#include "ft_input.h"
#include "ft_string.h"
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

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
	size_t	len;
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
	{
		p_mini->should_exit = TRUE;
		return (0);
	}
	else
	{
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
	}
	if (line && *line)
		add_history(line);
	restore_sigquit();
	init_args(args);
	ret = ft_split_args(p_tokens, line, args);
	free(line);
	return (ret);
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

