/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:09:17 by cviel             #+#    #+#             */
/*   Updated: 2025/08/19 18:49:35 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "expand.h"
#include "ft_vectors.h"
#include "ft_memory.h"

static int	fill_splitted(t_vector *p_splitted, t_vector copy);

/*	ft_vector_init -> OK
	fill_splitted -> OK */
int	word_split(t_vector *p_splitted)
{
	int			ret;
	t_vector	copy;

	ft_vector_copy(&copy, p_splitted);
	ft_bzero(p_splitted, sizeof(t_vector));
	ret = ft_vector_init(p_splitted, 5, sizeof(t_vector), free_splitted);
	if (ret != 0)
	{
		ft_vector_free(&copy);
		return (ret);
	}
	ret = fill_splitted(p_splitted, copy);
	ft_vector_free(&copy);
	return (ret);
}

/*	ft_vector_init -> OK
	fill_word -> OK
	ft_vector_add_single -> OK*/
static int	build_word(t_vector *p_splitted, t_vector copy,
	size_t *p_vec_ind, size_t *p_ind)
{
	int			ret;
	t_vector	word;

	ret = ft_vector_init(&word, 5, copy.data_size, copy.del);
	if (ret != 0)
		return (ret);
	ret = fill_word(&word, copy, p_vec_ind, p_ind);
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

/*	build_word -> OK */
static int	fill_splitted(t_vector *p_splitted, t_vector copy)
{
	int		ret;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < copy.size)
	{
		ret = build_word(p_splitted, copy, &i, &j);
		if (ret != 0)
			return (ret);
	}
	return (0);
}
