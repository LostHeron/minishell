/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:27:31 by cviel             #+#    #+#             */
/*   Updated: 2025/08/05 18:07:44 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "expand.h"
#include "ft_vectors.h"
#include "ft_memory.h"
#include "ft_string.h"

static int	expand_pattern(t_vector *p_splitted, size_t *p_vec_ind);

int	expand_wildcard(t_vector *p_splitted)
{
	int		ret;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < p_splitted->size)
	{
		j = 0;
		while (j < ((t_vector *)p_splitted->data)[i].size)
		{
			if (((t_exp *)((t_vector *)
					p_splitted->data)[i].data)[j].quote == NONE
				&& ft_strchr(((t_exp *)((t_vector *)
					p_splitted->data)[i].data)[j].content, '*') != NULL)
			{
				ret = expand_pattern(p_splitted, &i);
				if (ret != 0)
					return (ret);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	fill_info(t_vector *p_pattern, t_vector word, size_t vec_ind)
{
	int		ret;
	t_pat	elem;
	size_t	i;

	i = 0;
	while (((t_exp *)word.data)[vec_ind].content[i] != '\0')
	{
		elem.c = ((t_exp *)word.data)[vec_ind].content[i];
		elem.wild = (elem.c == '*'
				&& ((t_exp *)word.data)[vec_ind].quote == NONE);
		ret = ft_vector_add_single(p_pattern, &elem);
		if (ret != 0)
			return (ret);
		i++;
	}
	return (0);
}

static int	get_pattern(t_vector *p_pattern, t_vector word)
{
	int		ret;
	size_t	i;

	ft_bzero(p_pattern, sizeof(t_vector));
	ret = ft_vector_init(p_pattern, 5, sizeof(t_pat), free_data);
	if (ret != 0)
		return (ret);
	i = 0;
	while (i < word.size)
	{
		ret = fill_info(p_pattern, word, i);
		if (ret != 0)
			return (ret);
		i++;
	}
	return (0);
}

static int	expand_pattern(t_vector *p_splitted, size_t *p_vec_ind)
{
	int			ret;
	t_vector	pattern;
	t_vector	names;

	ret = get_pattern(&pattern, ((t_vector *)p_splitted->data)[*p_vec_ind]);
	if (ret != 0)
	{
		ft_vector_free(&pattern);
		return (ret);
	}
	ret = find_match(&names, pattern);
	if (names.size == 0 || ret != 0)
	{
		ft_vector_free(&names);
		ft_vector_free(&pattern);
		return (ret);
	}
	ret = handle_wildcard(p_splitted, p_vec_ind, names);
	ft_vector_free(&names);
	return (ret);
}
