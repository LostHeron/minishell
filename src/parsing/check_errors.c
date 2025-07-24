/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:00:16 by jweber            #+#    #+#             */
/*   Updated: 2025/07/23 17:51:52 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_vectors.h"
#include "parsing.h"
#include "ft_io.h"
#include "ft_string.h"

static int	check_around_parenthesis(t_vector *p_tokens);

int	check_errors(t_minishell *p_mini, t_vector *p_tokens)
{
	int	ret;

	ret = check_error_syntax(*p_tokens);
	if (ret != 0)
		return (ret);
	ret = check_matching_parenthesis(p_tokens);
	if (ret != 0)
		return (ret);
	ret = check_around_parenthesis(p_tokens);
	if (ret != 0)
		return (ret);
	ret = prepare_here_doc(p_mini, p_tokens);
	if (ret != 0)
		return (ret);
	return (0);
}

static int	check_around_parenthesis(t_vector *p_tokens)
{
	size_t	token_i;
	int		ret;

	token_i = 0;
	while (token_i < p_tokens->size -1)
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
