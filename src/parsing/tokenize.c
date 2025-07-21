/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:24:04 by jweber            #+#    #+#             */
/*   Updated: 2025/07/04 16:03:30 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "minishell.h"
#include "ft_vectors.h"
#include "parsing.h"

int	tokenize(t_minishell *p_mini, t_vector *p_tokens)
{
	int		ret;

	ret = line_to_tokens(p_mini, p_tokens);
	if (rl_done != 0)
		return (0);
	if (ret != 0)
	{
		return (ret);
	}
	ret = check_errors(p_mini, p_tokens);
	if (ret != 0)
	{
		ft_vector_free(p_tokens);
		return (ret);
	}
	return (0);
}
