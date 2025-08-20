/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:14:09 by cviel             #+#    #+#             */
/*   Updated: 2025/08/20 13:55:47 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "expand.h"
#include "ft_vectors.h"
#include "ft_string.h"
#include "ft_memory.h"

static int	init_replace(t_vector *p_splitted,
				t_vector *p_copy, size_t vec_ind);
static int	replace_wildcard(t_vector *p_splitted,
				t_vector names, size_t *p_vec_ind);
static int	end_replace(t_vector *p_splitted, t_vector copy, size_t vec_ind);

int	handle_wildcard(t_vector *p_splitted, size_t *p_vec_ind, t_vector names)
{
	int			ret;
	t_vector	copy;
	size_t		copy_i;

	ret = init_replace(p_splitted, &copy, *p_vec_ind);
	if (ret != 0)
	{
		ft_vector_free(&copy);
		return (ret);
	}
	copy_i = *p_vec_ind + 1;
	ret = replace_wildcard(p_splitted, names, p_vec_ind);
	if (ret != 0)
	{
		ft_vector_free(&copy);
		return (ret);
	}
	ret = end_replace(p_splitted, copy, copy_i);
	ft_vector_free(&copy);
	return (ret);
}

/*	ft_vector_init -> OK
	ft_vector_add_single ->*/
static int	init_replace(t_vector *p_splitted,
	t_vector *p_copy, size_t vec_ind)
{
	int		ret;
	size_t	i;
	static int a;

	#include <stdio.h>
	printf("vec_ind = %zu\n", vec_ind);
	a++;
	ft_vector_copy(p_copy, p_splitted);
	ft_bzero(p_splitted, sizeof(t_vector));
	ret = ft_vector_init(p_splitted, 5, p_copy->data_size, p_copy->del);
	if (ret != 0)
		return (ret);
	i = 0;
	while (i < vec_ind)
	{
		if (a >= 0)
			ret = ERROR_MALLOC;
		else
			ret = ft_vector_add_single(p_splitted, &((t_vector *)p_copy->data)[i]);
		if (ret != 0)
			return (ret);
		i++;
	}
	return (0);
}

static int	add_name(t_vector *p_splitted, t_vector names, size_t name_ind)
{
	int			ret;
	t_vector	word;
	t_exp		exp;

	ret = ft_vector_init(&word, 1, sizeof(t_exp), free_exp);
	if (ret != 0)
		return (ret);
	exp.content = ft_strdup(((char **)names.data)[name_ind]);
	if (exp.content == NULL)
	{
		ft_vector_free(&word);
		return (ERROR_MALLOC);
	}
	ret = ft_vector_add_single(&word, &exp);
	if (ret != 0)
	{
		free(exp.content);
		ft_vector_free(&word);
		return (ret);
	}
	ret = ft_vector_add_single(p_splitted, &word);
	if (ret != 0)
		ft_vector_free(&word);
	return (ret);
}

static int	replace_wildcard(t_vector *p_splitted,
	t_vector names, size_t *p_vec_ind)
{
	int			ret;
	size_t		i;

	i = 0;
	while (i < names.size)
	{
		ret = add_name(p_splitted, names, i);
		if (ret != 0)
			return (ret);
		(*p_vec_ind)++;
		i++;
	}
	return (0);
}

static int	end_replace(t_vector *p_splitted, t_vector copy, size_t vec_ind)
{
	int	ret;

	while (vec_ind < copy.size)
	{
		ret = ft_vector_add_single(p_splitted,
				&((t_vector *)copy.data)[vec_ind]);
		if (ret != 0)
			return (ret);
		vec_ind++;
	}
	return (0);
}
