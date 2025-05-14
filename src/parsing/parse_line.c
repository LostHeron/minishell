/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:43:05 by jweber            #+#    #+#             */
/*   Updated: 2025/05/14 18:15:27 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include <stdlib.h>

int	parse_line(char *line, t_ast **p_ast)
{
	char	**token;
	int		err_code;

	(void) line;
	(void) p_ast;
	err_code = 0;
	token = ft_split_args(line, NULL, &err_code);
	if (err_code != 0)
		return (err_code);
	return (0);
}
