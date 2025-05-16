/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:43:05 by jweber            #+#    #+#             */
/*   Updated: 2025/05/16 10:30:54 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "parsing.h"
#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

int	parse_line(char *line, t_ast **p_ast)
{
	t_vector	tokens;
	char		**args;
	int			err_code;

	(void) line;
	(void) p_ast;
	err_code = 0;
	args = init_args(&err_code);
	if (err_code != 0)
		return (err_code);
	tokens = ft_split_args(line, args, &err_code);
	if (err_code != 0)
		return (err_code);
	printf("before for loop\n");
	printf("tokens.size = %zu\n", tokens.size);
	for (size_t i = 0; i < tokens.size; i++)
	{
		printf("-> '%s'\n", ((char **)tokens.data)[i]);
	}
	return (0);
}
