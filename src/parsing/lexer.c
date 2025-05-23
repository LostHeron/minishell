/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:43:05 by jweber            #+#    #+#             */
/*   Updated: 2025/05/16 14:25:37 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "parsing.h"
#include <stdlib.h>
#include <stdio.h>

int	lexer(char *line, t_vector *p_tokens)
{
	char	**args;
	int		err_code;

	err_code = 0;
	args = init_args(&err_code);
	if (err_code != 0)
		return (err_code);
	*p_tokens = ft_split_args(line, args, &err_code);
	if (err_code != 0)
		return (err_code);
	printf("before for loop\n");
	printf("tokens.size = %zu\n", p_tokens->size);
	for (size_t i = 0; ((char **)p_tokens->data)[i] != NULL; i++)
	{
		printf("-> '%s'\n", ((char **)p_tokens->data)[i]);
	}
	free(args);
	return (0);
}
