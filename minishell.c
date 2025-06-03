/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:37:10 by jweber            #+#    #+#             */
/*   Updated: 2025/06/03 16:31:42 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "ft_string.h"
#include "ft_vectors.h"
#include "minishell.h"
#include "parsing.h"
#include "printing.h"
#include <errno.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "printing.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	int			err_code;
	t_vector	tokens;
	int			ret;
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
	}
	while (err_code == 0)
	{
		//errno = 0;
		line = readline("prompt >> ");
		if (line == NULL)
			exit(0);//break ;
		//printf("errno = %i\n", errno);
		ret = lexer(line, &tokens);
		if (ret != 0)
		{
			print_error(ret);
		}
		else
		{
			printf("line = %s\n", line);
		}
		free(line);
		i = 0;
		ast = create_ast(tokens, END_LINE, &i);
		if (!ast)
			return (1);
		if (ft_strcmp(((char **)tokens.data)[0], "exit") == 0)
			err_code = 1;
		ft_vector_free(&tokens);
		print_tree(ast, 0);
		minishell.previous_side = PREV_NONE;
		minishell.previous_type = 0; //NONE;
		exec_command(ast, &minishell);
		wait(NULL);
		free_tree(&ast);
	}
	free_minishell(&minishell);
	return (0);
}
