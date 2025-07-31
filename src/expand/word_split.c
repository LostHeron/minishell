/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:09:17 by cviel             #+#    #+#             */
/*   Updated: 2025/07/31 23:13:38 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "expand.h"
#include "ft_vectors.h"
#include "ft_string.h"
#include "ft_memory.h"
#include <stdio.h>
static int	build_word(t_vector *p_splitted, t_vector copy,
				size_t *p_vec_ind, size_t *p_ind);

int	word_split(t_vector *p_splitted)
{
	int			ret;
	t_vector	copy;
	size_t		i;
	size_t		j;

	ft_vector_copy(&copy, p_splitted);
	ft_bzero(p_splitted, sizeof(t_vector));
	ret = ft_vector_init(p_splitted, 5, sizeof(t_vector), free_splitted);
	if (ret != 0)
	{
		ft_vector_free(&copy);
		return (ret);
	}
	i = 0;
	j = 0;
	while (i < copy.size)
	{
		ret = build_word(p_splitted, copy, &i, &j);
		if (ret != 0)
		{
			ft_vector_free(&copy);
			return (ret);
		}
	}
	return (0);
}

static size_t	end_word(t_vector copy, size_t *p_vec_ind, size_t *p_ind)
{
	size_t	i;

	while (((t_exp *)copy.data)[*p_vec_ind].content[*p_ind] != '\0'
			&& ft_strchr(WHITE_SPACES,
			((t_exp *)copy.data)[*p_vec_ind].content[*p_ind]) != NULL)
				(*p_ind)++;
	i = 0;
	while (((t_exp *)copy.data)[*p_vec_ind].content[*p_ind + i] != '\0'
			&& ft_strchr(WHITE_SPACES,
			((t_exp *)copy.data)[*p_vec_ind].content[*p_ind + i]) == NULL)
		i++;
	if (i == 0)
	{
		(*p_vec_ind)++;
		(*p_ind) = 0;
	}
	return (i);
}

static int	unquoted_split(t_vector *p_word, t_vector copy,
				size_t *p_vec_ind, size_t *p_ind)
{
	int		ret;
	t_exp	exp;
	size_t	i;
	
	i = end_word(copy, p_vec_ind, p_ind);
	if (i == 0)
		return (0);
	exp.quote = NONE;
	exp.content = ft_strndup(&((t_exp *)
				copy.data)[*p_vec_ind].content[*p_ind], i);
	if (exp.content == NULL)
		return (ERROR_MALLOC);
	(*p_ind) += i;
	if (((t_exp *)copy.data)[*p_vec_ind].content[*p_ind] == '\0')
	{
		(*p_vec_ind)++;
		(*p_ind) = 0;
	}
	ret = ft_vector_add_single(p_word, &exp);
	if (ret != 0)
		free(exp.content);
	return (ret);
}

static int	add_to_word(t_vector *p_word, t_vector copy,
				size_t *p_vec_ind, size_t *p_ind)
{
	int	ret;

	while (*p_vec_ind < copy.size)	
	{
		if (((t_exp *)copy.data)[*p_vec_ind].quote == NONE)
		{
			ret = unquoted_split(p_word, copy, p_vec_ind, p_ind);
			if (ret != 0 || *p_vec_ind >= copy.size
				|| ft_strchr(WHITE_SPACES,
				((t_exp *)copy.data)[*p_vec_ind].content[*p_ind]) != NULL)
			{
				break ;
			}
		}
		else
		{
			ret = ft_vector_add_single(p_word,
					&((t_exp *)copy.data)[*p_vec_ind]);
			(*p_vec_ind)++;
		}
	}
	return (ret);
}

static int	build_word(t_vector *p_splitted, t_vector copy,
				size_t *p_vec_ind, size_t *p_ind)
{
	int			ret;
	t_vector	word;

	ret = ft_vector_init(&word, 5, copy.data_size, copy.del);
	if (ret != 0)
		return (ret);
	ret = add_to_word(&word, copy, p_vec_ind, p_ind);
	if (ret != 0 || word.size == 0)
	{
		ft_vector_free(&word);
		return (ret);
	}
	ret = ft_vector_add_single(p_splitted, &word);
	if (ret != 0)
		ft_vector_free(&word);
	return (ret);
}
