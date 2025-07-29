/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:28:35 by jweber            #+#    #+#             */
/*   Updated: 2025/07/24 13:43:11 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "ft_init.h"
#include "ft_io.h"
#include "ft_vectors.h"
#include "handle_signal.h"
#include "minishell.h"
#include "parsing.h"
#include "printing.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int	start_minishell(t_minishell *p_mini);
static int	ast_ize(t_ast **p_ast, t_vector *p_tokens);
static int	run_exec(t_minishell *p_mini, t_ast **p_ast);

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
	init_signals();
	while (minishell.should_exit == FALSE)
	{
		if (g_my_signal == SIGINT)
			minishell.last_error_code = SIGINT + 128;
		if (g_my_signal == SIGQUIT)
			minishell.last_error_code = SIGQUIT + 128;
		g_my_signal = 0;
		rl_done = 0;
		ret = start_minishell(&minishell);
		if (ret != 0)
		{
			print_error(ret);
			if (ret < 0)
				minishell.should_exit = TRUE;
		}
	}
	free_minishell(&minishell);
	rl_clear_history();
	return (minishell.last_error_code);
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
	if (ret != 0)
		return (ret);
	if (g_my_signal != 0)
	{
		return (0);
	}
	if (tokens.size == 0)
	{
		ft_vector_free(&tokens);
		return (0);
	}
	ret = ast_ize(&ast, &tokens);
	if (ret != 0)
		return (ret);
	p_mini->head_ast = ast;
	ret = run_exec(p_mini, &ast);
	if (ret != 0)
		return (ret);
	return (0);
}

/* to check :
 *	-> create_ast fail : DONE (from Corentin);
*/
static int	ast_ize(t_ast **p_ast, t_vector *p_tokens)
{
	size_t	i;	

	i = 0;
	*p_ast = create_ast(*p_tokens, END_LINE, &i);
	ft_vector_free(p_tokens);
	if (*p_ast == NULL)
		return (ERROR_MALLOC);
	return (0);
}

/* to check :
 *	-> pipe fail : TO DO ;
 *	-> exec_func fail : TO DO ;
 *	-> close_fd1 fail : TO DO ;
 *	-> wait_children fail : to check even ??
*/
static int	run_exec(t_minishell *p_mini, t_ast **p_ast)
{
	int	ret_exec;
	int	ret;
	int	final_ret;

	final_ret = 0;
	p_mini->previous_side = PREV_NONE;
	p_mini->previous_type = -1;
	ret = pipe(p_mini->fd1);
	if (ret == -1)
	{
		perror("pipe");
		free_tree(p_ast);
		return (ERROR_PIPE);
	}
	p_mini->first_cmd = 1;
	ret_exec = exec_func(*p_ast, p_mini);
	if (ret_exec != 0)
		final_ret = ret_exec;
	ret = close_fd1(p_mini);
	if (ret != 0 && final_ret == 0)
		final_ret = ret;
	wait_children(p_mini);
	free_tree(p_ast);
	return (final_ret);
}
