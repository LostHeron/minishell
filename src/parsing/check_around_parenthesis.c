/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_around_parenthesis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:02:11 by jweber            #+#    #+#             */
/*   Updated: 2025/08/04 18:02:31 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "ft_string.h"
#include "parsing.h"

int	check_around_parenthesis(t_vector *p_tokens)
{
	size_t	token_i;
	int		ret;

	token_i = 0;
	while (token_i < p_tokens->size)
	{
		ret = 0;
		if (ft_strcmp("(", ((char **)p_tokens->data)[token_i]) == 0)
		{
			ret = check_around_opening_parenthesis(p_tokens, token_i);
		}
		else if (ft_strcmp(")", ((char **)p_tokens->data)[token_i]) == 0)
		{
			ret = check_around_closing_parenthesis(p_tokens, token_i);
		}
		if (ret != 0)
			return (ret);
		token_i++;
	}
	return (0);
}
