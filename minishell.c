/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:37:10 by jweber            #+#    #+#             */
/*   Updated: 2025/05/16 14:23:51 by jweber           ###   ########.fr       */
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
#include <errno.h>

int	main(void)
{
	char		*line;
	int			err_code;
	t_vector	tokens;
	int			ret;
	t_ast		*ast;

	err_code = 0;
	(void) ast;
	while (err_code == 0)
	{
		//errno = 0;
		line = readline("prompt >> ");
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
		(void) ast;
		//ret = get_ast(&tokens, &ast);
		get_ast(tokens.data);
		//print_ast(ast);
		if (ft_strcmp(((char **)tokens.data)[0], "exit") == 0)
			err_code = 1;
		ft_vector_free(&tokens);
	}

	return (0);
}
