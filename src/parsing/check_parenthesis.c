/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:18:43 by jweber            #+#    #+#             */
/*   Updated: 2025/06/25 16:26:03 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_string.h"
#include "ft_vectors.h"
#include <stdlib.h>

int	check_parenthesis(t_vector *p_tokens)
{
	size_t	i;
	ssize_t	nb_parenthesis;

	nb_parenthesis = 0;
	i = 0;
	while (i < p_tokens->size)
	{
		if (ft_strcmp(((char **)p_tokens->data)[i], "(") == 0)
		{
			nb_parenthesis++;
			if (i != p_tokens->size
				&& ft_strcmp(((char **)p_tokens->data)[i + 1], ")") == 0)
				return (ERROR_EMPTY_PARENTHESIS);
		}
		if (ft_strcmp(((char **)p_tokens->data)[i], ")") == 0)
			nb_parenthesis--;
		if (nb_parenthesis < 0)
			return (ERROR_UNMATCHING_PARENTHESIS);
		i++;
	}
	if (nb_parenthesis == 0)
		return (0);
	else
		return (ERROR_UNMATCHING_PARENTHESIS);
}
