/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:27:31 by cviel             #+#    #+#             */
/*   Updated: 2025/07/29 19:04:21 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "expand.h"
#include "ft_vectors.h"
#include "ft_lists_single.h"
#include "ft_string.h"
#include <stdio.h>

static int	expand_here(t_vector *p_splitted,
				ssize_t *p_vec_ind, ssize_t *p_ind);
static int	expand_single(t_vector *p_splitted, ssize_t *p_vec_ind);

int	expand_wildcard(t_vector *p_splitted)
{
	int		ret;
	ssize_t	i;

	i = 0;
	while ((size_t)i < p_splitted->size)
	{
		if (((t_exp *)p_splitted->data)[i].quote == NONE)
		{
			ret = expand_single(p_splitted, &i);
			if (ret != 0)
				return (ret);
		}
		i++;
	}
	return (0);
}

static int	expand_single(t_vector *p_splitted, ssize_t *p_vec_ind)
{
	int		ret;
	ssize_t	i;

	i = 0;
	while ((size_t)(*p_vec_ind) < p_splitted->size
		&& ((t_exp *)p_splitted->data)[*p_vec_ind].content[i])
	{
		if (((t_exp *)p_splitted->data)[*p_vec_ind].content[i] == '*')
		{
			ret = expand_here(p_splitted, p_vec_ind, &i);
			if (ret != 0)
				return (ret);
		}
		else
			i++;
	}
	return (0);
}

static void	go_next(t_vector splitted,
				ssize_t *p_vec_ind, ssize_t *p_ind)
{
	while ((size_t)(*p_vec_ind) < splitted.size
		&& ((t_exp *)splitted.data)[*p_vec_ind].content[*p_ind] != '*')
	{
		if (((t_exp *)splitted.data)[*p_vec_ind].quote != NONE)
			(*p_vec_ind)++;
		else
		{
			(*p_ind)++;
			if (((t_exp *)
					splitted.data)[*p_vec_ind].content[*p_ind] == '\0')
			{
				(*p_vec_ind)++;
				(*p_ind) = 0;
			}
		}
	}
	(*p_ind)++;
}

static int	expand_here(t_vector *p_splitted,
				ssize_t *p_vec_ind, ssize_t *p_ind)
{
	int			ret;
	t_vector	pattern;
	char		*replace;

	pattern_start(*p_splitted, p_vec_ind, p_ind);
	ret = get_pattern(&pattern, *p_splitted, *p_vec_ind, *p_ind);
	if (ret != 0)
	{
		ft_vector_free(&pattern);
		return (ret);
	}
	replace = NULL;
	ret = find_match(&replace, pattern);
	if (replace == NULL || ret != 0)
	{
		free(replace);
		ft_vector_free(&pattern);
		go_next(*p_splitted, p_vec_ind, p_ind);
		return (ret);
	}
	ft_vector_free(&pattern);
	ret = handle_wildcard(p_splitted, p_vec_ind, p_ind, replace);
	free(replace);
	return (ret);
}
