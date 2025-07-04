/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:28:35 by jweber            #+#    #+#             */
/*   Updated: 2025/07/03 14:47:05 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "ft_vectors.h"
#include "handle_signal.h"
#include "ft_init.h"
#include "minishell.h"
#include "parsing.h"
#include "ft_io.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int	start_minishell(t_minishell *p_mini);
static int	ast_ize(t_ast **p_ast, t_vector *p_tokens);
static int	run_exec(t_minishell *p_mini, t_ast **p_ast);
static void	close_fd1(t_minishell *p_mini);

int	main(int argc, char **argv, char **env)
{
	int			ret;
	t_minishell	minishell;

	minishell.should_exit = FALSE;
	(void) argc;
	(void) argv;
	ret = init_minishell(&minishell, env); // checked !
	if (ret != 0)
	{
		ft_putstr_fd("starting initialisation failure, aborting\n", 2);
		return (1);
	}
	//init_signals();
	while (minishell.should_exit == FALSE)
	{
		ret = start_minishell(&minishell);
		if (ret != 0)
		{
			if (ret < 0)
				minishell.should_exit = TRUE;
			else
			{
				// continue program but display error message ?
				// I think do nothing if error code is not negativ !
				// return ?
				continue ;
			}
		}
	}
	free_minishell(&minishell);
	rl_clear_history();
	return (minishell.last_error_code);
}

static int	start_minishell(t_minishell *p_mini)
{
	int			ret;
	t_vector	tokens;
	t_ast		*ast;

	ret = tokenize(p_mini, &tokens);
	if (ret != 0)
	{
		return (ret);
	}
	ret = ast_ize(&ast, &tokens);
	if (ret != 0)
	{
		return (ret);
	}
	ret = run_exec(p_mini, &ast);
	if (ret != 0)
	{
		return (ret);
	}
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
	int	ret;

	p_mini->previous_side = PREV_NONE;
	p_mini->previous_type = -1;
	if (pipe(p_mini->fd1) == -1)
	{
		perror("fn : run_exec : pipe(p_mini->fd1)");
		free_tree(p_ast);
		return (1);
	}
	p_mini->first_cmd = 1;
	ret = exec_func(*p_ast, p_mini);
	if (ret != 0)
	{
		// do stuff ?
		// return ?
	}
	close_fd1(p_mini);
	ret = wait_children(p_mini);
	if (ret != 0)
	{
		// must exit program cuz should not happens in normal behaviour
		// so exit but nice way !
	}
	free_tree(p_ast);
	return (0);
}

static void	close_fd1(t_minishell *p_mini)
{
	if (p_mini->fd1[0] != -1)
		if (close(p_mini->fd1[0]) == -1)
			perror("minishell.c : main : (close(minishell.fd1[0])");
	p_mini->fd1[0] = -1;
	if (p_mini->fd1[1] != -1)
		if (close(p_mini->fd1[1]) == -1)
			perror("minishell.c : main : (close(minishell.fd1[1])");
	p_mini->fd1[1] = -1;
}
