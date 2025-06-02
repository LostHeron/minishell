/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:37:10 by jweber            #+#    #+#             */
/*   Updated: 2025/06/02 16:16:25 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "ft_vectors.h"
#include "parsing.h"
#include "printing.h"
#include "ft_string.h"
#include "ast.h"
#include "execution.h"
#include <errno.h>

int	main(void)
{
	char		*line;
	int			err_code;
	t_vector	tokens;
	int			ret;
	t_ast		*ast;
	size_t		i;

	err_code = 0;
	while (err_code == 0)
	{
		//errno = 0;
		line = readline("prompt >> ");
		if (line == NULL)
			exit (0);
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
		exec_command(ast);
		free_tree(&ast);
	}

	return (0);
}
