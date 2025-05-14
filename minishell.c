/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:37:10 by jweber            #+#    #+#             */
/*   Updated: 2025/05/14 18:07:01 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "parsing.h"
#include "printing.h"

int	main(void)
{
	char	*line;
	int		err_code;
	int		ret;
	t_ast	*ast;

	err_code = 0;
	while (err_code == 0)
	{
		line = readline("prompt >> ");
		ret = parse_line(line, &ast);
		if (ret != 0)
		{
			print_error(ret);
		}
		else
		{
			printf("line = %s\n", line);
		}
		print_ast(ast);
		free(line);
	}
	return (0);
}
