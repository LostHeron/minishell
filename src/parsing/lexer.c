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

int	lexer(char *line, t_vector *p_tokens)
{
	char	**args;
	int		ret;

	ret = init_args(&args);
	if (ret != 0)
		return (ret);
	ret = ft_split_args(p_tokens, line, args);
	free(args);
	return (ret);
}
