/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:28:35 by jweber            #+#    #+#             */
/*   Updated: 2025/07/01 17:40:18 by jweber           ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	char		*line;
	int			err_code;
	t_vector	tokens;
	int			ret;
	int			wait_id;
	t_ast		*ast;
	size_t		i;
	t_minishell	minishell;

	err_code = 0;
	(void) argc;
	(void) argv;
	ret = init_minishell(&minishell, env);
	if (ret != 0)
	{
		// do stuff ?
		//return ??
		return (1);
	}
	//init_signals();
	while (err_code == 0)
	{
		//errno = 0;
		line = readline("prompt >> ");
		if (line == NULL)
			exit(minishell.last_error_code);//break ;
		if (line && *line)
			add_history(line);
		ret = check_parenthesis(line);
		if (ret != 0)
		{
			free(line);
			print_error(ret);
			continue ;
		}
		ret = lexer(line, &tokens);
		if (ret != 0)
		{
			if (ret > 0)
			{
				free(line);
				print_error(ret);
			}
			else
			{
				// do stuff ?
				exit(1);
			}
		}
		else
		{
			printf("line = %s\n", line);
		}
		free(line);
		// first check for syntax error !
		// here or later should handle here document
		ret = check_error_syntax(tokens);
		if (ret != 0)
		{
			ft_putstr_fd("error syntax in check_error_syntax !\n", 2);
			continue ;
		}
		i = 0;
		if (tokens.size <= 0)
		{
			ft_putstr_fd("token.size == 0 -> continue and wait next input !\n", 2);
			ft_vector_free(&tokens);
			continue ;
		}
		init_here_doc_fds(minishell.fds_here_doc);
		ret = count_here_doc(tokens);
		if (ret != 0)
		{
			ft_putstr_fd("maximum here-document count exceeded\n", 2);
			continue ;
		}
		ret = get_here_doc(&minishell, &tokens);
		if (ret != 0)
		{
			ft_putstr_fd("problem occured in function 'get_here_doc'\n", 2);
			continue ;
		}
		ast = create_ast(tokens, END_LINE, &i);
		if (ast == NULL)
		{
			ft_putstr_fd("error synthax !\n", 2);
			continue ;
		}
		print_tree(ast, 0);
		if (ft_strcmp(((char **)tokens.data)[0], "exit") == 0)
			err_code = 1;
		ft_vector_free(&tokens);
		minishell.previous_side = PREV_NONE;
		minishell.previous_type = 0; //NONE;
		if (pipe(minishell.fd1) == -1)
		{
			// do stuff
			// return?
			;
		}
		minishell.first_cmd = 1;
		exec_func(ast, &minishell);
		if (minishell.fd1[0] != -1)
			if (close(minishell.fd1[0]) == -1)
				perror("minishell.c : main : (close(minishell.fd1[0])");
		minishell.fd1[0] = -1;
		if (minishell.fd1[1] != -1)
			if (close(minishell.fd1[1]) == -1)
				perror("minishell.c : main : (close(minishell.fd1[1])");
		minishell.fd1[1] = -1;
		wait_id = wait(NULL);
		while (wait_id != -1)
			wait_id = wait(NULL);
		free_tree(&ast);
	}
	free_minishell(&minishell);
	rl_clear_history();
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
