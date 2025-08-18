/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:22:56 by jweber            #+#    #+#             */
/*   Updated: 2025/08/14 10:55:37 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "ft_init.h"
#include "ft_io.h"
#include "ft_vectors.h"
#include "handle_signal.h"
#include "minishell.h"
#include "freeing.h"
#include "parsing.h"
#include "printing.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	run_minishell(t_minishell *p_mini);
static int	start_minishell(t_minishell *p_mini);
static int	ast_ize(t_ast **p_ast, t_vector *p_tokens);

int	g_my_signal;

/* to check :
 *	- init_minishell : DONE -> OK !
 *	- start_minishell failure : TO DO !
 *	- 
*/
int	main(int argc, char **argv, char **env)
{
	int			ret;
	t_minishell	minishell;

	minishell.should_exit = FALSE;
	(void) argc;
	(void) argv;
	ret = init_minishell(&minishell, env);
	if (ret != 0)
	{
		ft_putstr_fd("starting initialisation failure, aborting\n", 2);
		return (1);
	}
	while (minishell.should_exit == FALSE)
	{
		run_minishell(&minishell);
	}
	ret = free_minishell(&minishell);
	rl_clear_history();
	return (minishell.last_error_code);
}

static void	run_minishell(t_minishell *p_mini)
{
	int	ret;

	if (g_my_signal == SIGINT)
		p_mini->last_error_code = SIGINT + 128;
	if (g_my_signal == SIGQUIT)
		p_mini->last_error_code = SIGQUIT + 128;
	g_my_signal = 0;
	rl_done = 0;
	p_mini->is_error_syntax = 0;
	init_signals();
	init_here_doc_fds(p_mini);
	ret = start_minishell(p_mini);
	if (isatty(0) == 0 && p_mini->is_error_syntax == TRUE)
		p_mini->should_exit = TRUE;
	if (ret != 0 && g_my_signal == 0 && p_mini->print_error == 1)
		print_error(ret);
	close_here_doc_fds(p_mini);
}

/* to check
 *	-> tokenize fail : DONE -> OK !
 *	-> ast_ize fail : DONE -> OK !
 *	-> run_exec fail : TO DO ;
*/
static int	start_minishell(t_minishell *p_mini)
{
	int			ret;
	t_vector	tokens;
	t_ast		*ast;

	ret = tokenize(p_mini, &tokens);
	if (ret != 0 || g_my_signal != 0)
		return (ret);
	if (p_mini->should_exit == 1)
		return (0);
	if (tokens.size == 0)
	{
		ft_vector_free(&tokens);
		return (0);
	}
	ret = ast_ize(&ast, &tokens);
	if (ret != 0)
		return (ret);
	p_mini->head_ast = ast;
	return (run_exec(p_mini, &ast));
}

/* to check :
 *	-> create_ast fail : DONE (from Corentin);
*/
static int	ast_ize(t_ast **p_ast, t_vector *p_tokens)
{
	size_t	i;	

	i = 0;
	*p_ast = create_ast(*p_tokens, END_LINE_PRIO, &i);
	ft_vector_free(p_tokens);
	if (*p_ast == NULL)
		return (ERROR_MALLOC);
	return (0);
}
