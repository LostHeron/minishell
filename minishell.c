/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:28:35 by jweber            #+#    #+#             */
/*   Updated: 2025/07/02 15:28:25 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "ft_string.h"
#include "ft_vectors.h"
#include "handle_signal.h"
#include "ft_init.h"
#include "minishell.h"
#include "parsing.h"
#include "printing.h"
#include "printing.h"
#include "ft_io.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	init_here_doc_fds(int fds[NB_MAX_HERE_DOC]);
static int	start_minishell(t_minishell *p_mini, int *p_err_code);
static int	tokenize(t_minishell *p_mini, t_vector *p_tokens, int *p_err_code);
static int	ast_ize(t_ast **p_ast, t_vector *p_tokens);
static int	run_exec(t_minishell *p_mini, t_ast **p_ast);

int	main(int argc, char **argv, char **env)
{
	int			err_code;
	int			ret;
	t_minishell	minishell;

	err_code = 0;
	(void) argc;
	(void) argv;
	ret = init_minishell(&minishell, env);
	if (ret != 0)
	{
		ft_putstr_fd("starting initialisation failure, aborting\n", 2);
		return (1);
	}
	//init_signals();
	while (err_code == 0)
	{
		ret = start_minishell(&minishell, &err_code);
		if (ret != 0)
		{
			if (ret < 0)
			{
				// should exit program properly !
				;
			}
			else
			{
				// continue program but display error message ?
				// return ?
				;
			}
		}
	}
	free_minishell(&minishell);
	rl_clear_history();
	return (minishell.last_error_code);
}

static int	start_minishell(t_minishell *p_mini, int *p_err_code)
{
	int			ret;
	t_vector	tokens;
	t_ast		*ast;

	ret = tokenize(p_mini, &tokens, p_err_code);
	if (ret != 0)
	{
		// do stuff !
		// return ?
	}
	if (ft_strcmp(((char **)tokens.data)[0], "exit") == 0)
	{
		*p_err_code = 1;
		return (0);
	}
	ret = ast_ize(&ast, &tokens);
	if (ret != 0)
	{
		// do stuff 
		// return ?
	}
	ret = run_exec(p_mini, &ast);
	if (ret != 0)
	{
		// do stuff
		// return ?
	}
	return (0);
}

static int	tokenize(t_minishell *p_mini, t_vector *p_tokens, int *p_err_code)
{
	char	*line;
	int		ret;

	line = readline("prompt >> ");
	if (line == NULL)
	{
		*p_err_code = 1;
		return (0);
	}
	if (line && *line)
		add_history(line);
	ret = check_parenthesis(line);
	if (ret != 0)
	{
		free(line);
		print_error(ret);
		return (0);
	}
	ret = lexer(line, p_tokens);
	if (ret != 0)
	{
		if (ret > 0)
		{
			free(line);
			print_error(ret);
			p_mini->last_error_code = 2;
			return (0);
		}
		else
		{
			// do stuff ?
			return (ret);
		}
	}
	free(line);
	ret = check_error_syntax(*p_tokens);
	if (ret != 0)
	{
		ft_putstr_fd("error syntax in check_error_syntax !\n", 2);
		return (0);
	}
	if (p_tokens->size <= 0)
	{
		ft_putstr_fd("token.size == 0 -> continue and wait next input !\n", 2);
		ft_vector_free(p_tokens);
		return (0);
	}
	init_here_doc_fds(p_mini->fds_here_doc);
	ret = count_here_doc(*p_tokens);
	if (ret != 0)
	{
		ft_putstr_fd("maximum here-document count exceeded\n", 2);
		p_mini->last_error_code = 2;
		return (0);
	}
	ret = get_here_doc(p_mini, p_tokens);
	if (ret != 0)
	{
		ft_putstr_fd("problem occured in function 'get_here_doc'\n", 2);
		return (0);
	}
	return (0);
}

static int	ast_ize(t_ast **p_ast, t_vector *p_tokens)
{
	size_t	i;	

	i = 0;
	*p_ast = create_ast(*p_tokens, END_LINE, &i);
	if (*p_ast == NULL)
	{
		ft_putstr_fd("error synthax in ast !\n", 2);
		return (1);
	}
	print_tree(*p_ast, 0);
	ft_vector_free(p_tokens);
	return (0);
}

static int	run_exec(t_minishell *p_mini, t_ast **p_ast)
{
	//int	wait_id;
	int	ret;

	p_mini->previous_side = PREV_NONE;
	p_mini->previous_type = 0;
	if (pipe(p_mini->fd1) == -1)
	{
		// do stuff
		// return?
		return (1);
	}
	p_mini->first_cmd = 1;
	exec_func(*p_ast, p_mini);
	if (p_mini->fd1[0] != -1)
		if (close(p_mini->fd1[0]) == -1)
			perror("minishell.c : main : (close(minishell.fd1[0])");
	p_mini->fd1[0] = -1;
	if (p_mini->fd1[1] != -1)
		if (close(p_mini->fd1[1]) == -1)
			perror("minishell.c : main : (close(minishell.fd1[1])");
	p_mini->fd1[1] = -1;
	ret = wait_children(p_mini);
	if (ret != 0)
	{
		// must exit program cuz should not happens in normal behaviour
		// so exit but nice way !
	}
	/*
	if (p_mini->last_child_id != 0)
	{
		wait_id = wait(&ret);
		{
			while (wait_id != -1)
			{
				if (wait_id == p_mini->last_child_id)
					if (WIFEXITED(ret) != 0)
						p_mini->last_error_code = WEXITSTATUS(ret);
				wait_id = wait(&ret);
			}
		}
	}
	*/
	free_tree(p_ast);
	return (0);
}

static void	init_here_doc_fds(int fds[NB_MAX_HERE_DOC])
{
	size_t	i;

	i = 0;
	while (i < NB_MAX_HERE_DOC)
	{
		fds[i] = -1;
		i++;
	}
	return ;
}
