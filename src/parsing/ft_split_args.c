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

void	my_free(t_vector *p_vec);

/* this is the first split, which should separat all key word one by one !
 * this is achived by providing a list of the 'reserved key word as args'
 * like : args[0] = "&&", args[1] = "if", args[4] = "|", ..., args[n] = ">"
 * and this list is used on each place on the line to separate each token 
 * independantly !
 *
 * NOTE ! : args order is important and all args should be placed in order of 
 * precedance !
 *
 * function should return a structur t_vector with all pointer in case of success
 * in case of failure, it should return NULL 
 * and have freed all it had begun allocating
*/
t_vector	ft_split_args(char *line, char **args, int *p_err_code)
{
	t_vector	tokens;
	char		*token_i;
	int			ret;
	char		*null_string;

	ret = ft_vector_init(&tokens, 5, sizeof(char *), &my_free);
	if (ret != 0)
	{
		*p_err_code = ret;
		return (tokens);
	}
	while (line[0])
	{
		while (line[0] && ft_strchr(WHITE_SPACES, line[0]) != NULL)
			line++;
		token_i = get_next_token(&line, args, p_err_code);
		if (*p_err_code != 0)
		{
			return (tokens);
		}
		ret = ft_vector_add_single(&tokens, &token_i);
		if (ret != 0)
		{
			*p_err_code = ret;
			return (tokens);
		}
	}
	null_string = NULL;
	ret = ft_vector_add_single(&tokens, &null_string);
	if (ret != 0)
	{
		// DO STUFF AND RETURN !
		*p_err_code = ret;
		return (tokens);
	}
	if (token_i == NULL)
	{
		return (tokens);
	}
	return (tokens);
	/*
	while (line[i])
	{
		ft_strstr_args(line, args);
	}
	*/
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
