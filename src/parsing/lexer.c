/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:43:05 by jweber            #+#    #+#             */
/*   Updated: 2025/07/04 16:02:42 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "parsing.h"
#include <stdlib.h>

static void	init_args(char **p_args);

/* to check
 *	-> init_args fail : TO DO ;
 *	-> ft_splitargs : TO DO ;
*/
int	lexer(char *line, t_vector *p_tokens)
{
	char	*args[11];

	init_args(args);
	return (ft_split_args(p_tokens, line, args));
}

static void	init_args(char **p_args)
{
	p_args[10] = NULL;
	p_args[0] = "&&";
	p_args[1] = "||";
	p_args[2] = "<<";
	p_args[3] = ">>";
	p_args[4] = "|";
	p_args[5] = "&";
	p_args[6] = ">";
	p_args[7] = "<";
	p_args[8] = "(";
	p_args[9] = ")";
}
