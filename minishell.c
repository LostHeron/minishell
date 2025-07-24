/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:28:35 by jweber            #+#    #+#             */
/*   Updated: 2025/07/18 13:57:41 by jweber           ###   ########.fr       */
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
		g_my_signal = 0;
		rl_done = 0;
		ret = start_minishell(&minishell);
		if (g_my_signal != 0)
		{
			continue;
		}
		if (ret != 0)
		{
			if (ret < 0)
				minishell.should_exit = TRUE;
			else
			{
				// continue program but display error message ?
				// I think do nothing if error code is not negativ !
				// return ?
				print_error(ret);
				continue ;
			}
		}
	}
	free_minishell(&minishell);
	rl_clear_history();
	return (minishell.last_error_code);
}

/* to check
 *	-> tokenize fail : TO DO ;
 *	-> ast_ize fail : TO DO ;
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
		return (0);
	ret = ast_ize(&ast, &tokens);
	if (ret != 0)
		return (ret);
	p_mini->head_ast = ast;
	ret = run_exec(p_mini, &ast);
	if (ret != 0)
		return (ret);
	return (0);
}

static int	ast_ize(t_ast **p_ast, t_vector *p_tokens)
{
	size_t	i;	

	i = 0;
	*p_ast = create_ast(*p_tokens, END_LINE, &i);
	ft_vector_free(p_tokens);
	if (*p_ast == NULL)
	{
		ft_putstr_fd("error synthax in ast !\n", 2);
		return (1);
	}
	return (0);
}

static int	run_exec(t_minishell *p_mini, t_ast **p_ast)
{
	int	ret_exec;

	p_mini->previous_side = PREV_NONE;
	p_mini->previous_type = -1;
	if (pipe(p_mini->fd1) == -1)
	{
		perror("fn : run_exec : pipe(p_mini->fd1)");
		free_tree(p_ast);
		return (ERROR_PIPE);
	}
	p_mini->first_cmd = 1;
	ret_exec = exec_func(*p_ast, p_mini);
	close_fd1(p_mini);
	wait_children(p_mini);
	free_tree(p_ast);
	if (ret_exec != 0)
	{
		// do stuff ?
		// return ?
		// faut wait dans tous les cas !
		return (ret_exec);
	}
	return (0);
}
