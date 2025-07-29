/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:24:04 by jweber            #+#    #+#             */
/*   Updated: 2025/07/23 15:00:02 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "handle_signal.h"
#include "minishell.h"
#include "ft_vectors.h"
#include "parsing.h"

/* to check
 *	-> line_to_tokens fail : DONE -> OK !
 *	-> check_errors fail : DONE -> OK !
*/
int	tokenize(t_minishell *p_mini, t_vector *p_tokens)
{
	int		ret;

	ret = line_to_tokens(p_mini, p_tokens);
	if (ret != 0)
		return (ret);
	if (g_my_signal != 0)
		return (0);
	ret = check_errors(p_mini, p_tokens);
	if (ret != 0)
	{
		ft_vector_free(p_tokens);
		return (ret);
	}
	return (0);
}
