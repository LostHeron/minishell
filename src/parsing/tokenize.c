/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:24:04 by jweber            #+#    #+#             */
/*   Updated: 2025/08/06 14:57:35 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "handle_signal.h"
#include "minishell.h"
#include "ft_vectors.h"
#include "parsing.h"
#include "check_errors.h"
#include <signal.h>
#include "ft_memory.h"

static void	check_error_failure(t_minishell *p_mini, t_vector *p_tokens,
				int ret);
static void	restore_sigquit(void);
static void	do_nothing(int sig);

/* This function should :
 *	-> return a t_vector of char ** of the different argument of the command !
 *
 * to check
 *	-> line_to_tokens fail : DONE -> OK !
 *	-> check_errors fail : DONE -> OK !
*/
int	tokenize(t_minishell *p_mini, t_vector *p_tokens)
{
	int		ret;

	ret = line_to_tokens(p_mini, p_tokens);
	if (ret != 0)
		return (ret);
	if (p_mini->should_exit == 1)
		return (0);
	if (g_my_signal != 0)
		return (0);
	ret = check_errors(p_mini, p_tokens);
	if (ret != 0)
	{
		check_error_failure(p_mini, p_tokens, ret);
		return (ret);
	}
	ret = prepare_here_docs(p_mini, p_tokens);
	if (ret != 0)
	{
		ft_vector_free(p_tokens);
		return (ret);
	}
	restore_sigquit();
	return (0);
}

static void	check_error_failure(t_minishell *p_mini, t_vector *p_tokens,
							int ret)
{
	if (ret > 0)
	{
		p_mini->is_error_syntax = 1;
		p_mini->last_error_code = 2;
	}
	ft_vector_free(p_tokens);
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
