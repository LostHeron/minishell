/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:23:59 by jweber            #+#    #+#             */
/*   Updated: 2025/05/15 12:57:36 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_vectors.h"
#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>

static int	extract_tokens(t_vector *p_tokens, char **p_token_i, \
								char **p_line, char **args);
void		my_free(t_vector *p_vec);

/*
 * This function should initialize t_vector of tokens !
 * in case of success : 
 *	return (0) and have initialized correctly t_vector structure
 * int case of failure:
 *	return non null integer and have freed correctly the t_vector structure !
*/
int	ft_split_args(t_vector *p_tokens, char *line, char **args)
{
	char		*token_i;
	int			ret;

	ret = ft_vector_init(p_tokens, 5, sizeof(char *), &my_free);
	if (ret != 0)
		return (ret);
	while (line[0])
	{
		ret = extract_tokens(p_tokens, &token_i, &line, args);
		if (ret != 0)
		{
			return (ret);
		}
	}
	if (token_i == NULL)
	{
		return (0);
	}
	return (0);
}

static int	extract_tokens(t_vector *p_tokens, char **p_token_i, \
								char **p_line, char **args)
{
	int	ret;

	while ((*p_line)[0] && ft_strchr(WHITE_SPACES, (*p_line)[0]) != NULL)
		(*p_line)++;
	ret = get_next_token(p_token_i, p_line, args);
	if (ret != 0)
	{
		ft_vector_free(p_tokens);
		return (ret);
	}
	if (*p_token_i != NULL)
	{
		ret = ft_vector_add_single(p_tokens, p_token_i);
		if (ret != 0)
		{
			ft_vector_free(p_tokens);
			return (ret);
		}
	}
	return (0);
}

void	my_free(t_vector *p_vec)
{
	size_t	i;

	i = 0;
	while (i < p_vec->size)
	{
		free(((char **)p_vec->data)[i]);
		i++;
	}
	free(p_vec->data);
}
