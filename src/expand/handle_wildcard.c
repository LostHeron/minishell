/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:14:09 by cviel             #+#    #+#             */
/*   Updated: 2025/07/30 19:19:56 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "expand.h"
#include "ft_vectors.h"
#include "ft_string.h"

static int	init_replace(t_vector *p_splitted,
				t_vector *p_copy, ssize_t vec_ind);
static int	replace_wildcard(t_vector *p_splitted, t_vector copy,
				t_ind *p_ind, char *replace);
static int	end_replace(t_vector *p_splitted, t_vector copy, ssize_t vec_ind);

int	handle_wildcard(t_vector *p_splitted,
			ssize_t *p_vec_ind, ssize_t *p_ind, char *replace)
{
	int			ret;
	t_vector	copy;
	t_ind		ind;

	ret = init_replace(p_splitted, &copy, *p_vec_ind);
	if (ret != 0)
	{
		ft_vector_free(&copy);
		return (ret);
	}
	ind.vec = p_vec_ind;
	ind.elt = p_ind;
	ret = replace_wildcard(p_splitted, copy, &ind, replace);
	if (ret != 0)
	{
		ft_vector_free(&copy);
		return (ret);
	}
	ret = end_replace(p_splitted, copy, *p_vec_ind);
	ft_vector_free(&copy);
	return (ret);
}

static int	init_replace(t_vector *p_splitted,
				t_vector *p_copy, ssize_t vec_ind)
{
	int		ret;
	int		i;

	ft_vector_copy(p_copy, p_splitted);
	ret = ft_vector_init(p_splitted, 5, p_copy->data_size, p_copy->del);
	if (ret != 0)
		return (ret);
	i = 0;
	while (i < vec_ind)
	{
		ret = ft_vector_add_single(p_splitted, &((t_exp *)p_copy->data)[i]);
		if (ret != 0)
			return (ret);
		i++;
	}
	return (0);
}

static int	join_end(t_exp *p_exp, t_vector copy, t_ind p_ind)
{
	while ((size_t)(*(p_ind.vec)) < copy.size)
	{
		if (((t_exp *)copy.data)[*(p_ind.vec)].quote == NONE
			&& ft_strchr(WHITE_SPACES,
			((t_exp *)copy.data)[*(p_ind.vec)].content[*(p_ind.elt)]) != NULL)
		{
			p_exp->content = ft_strjoin_free_first(p_exp->content,
					&((t_exp *)copy.data)[*(p_ind.vec)].content[*(p_ind.elt)]);
			if (p_exp->content == NULL)
				return (ERROR_MALLOC);
			return (0);
		}
		else
		{
			*(p_ind.elt) += 1;
			if (((t_exp *)copy.data)[*(p_ind.vec)].content[*(p_ind.elt)]
					== '\0')
			{
				*(p_ind.vec) += 1;
				*(p_ind.elt) = 0;
			}
		}
	}
	return (0);
}

static int	replace_wildcard(t_vector *p_splitted, t_vector copy,
				t_ind *p_ind, char *replace)
{
	int		ret;
	t_exp	exp;

	exp.quote = NONE;
	exp.content = NULL;
	if (*(p_ind->elt) != 0)
	{
		exp.content = ft_strndup(((t_exp *)copy.data)[*(p_ind->vec)].content,
				*(p_ind->elt) - 1);
		if (exp.content == NULL)
			return (ERROR_MALLOC);
	}
	exp.content = ft_strjoin_free_first(exp.content, replace);
	if (exp.content == NULL)
		return (ERROR_MALLOC);
	ret = join_end(&exp, copy, *p_ind);
	if (ret != 0)
	{
		free(exp.content);
		return (ret);
	}
	return (ft_vector_add_single(p_splitted, &exp));
}

static int	end_replace(t_vector *p_splitted, t_vector copy, ssize_t vec_ind)
{
	int	ret;

	while ((size_t)vec_ind < copy.size)
	{
		ret = ft_vector_add_single(p_splitted, &((t_exp *)copy.data)[vec_ind]);
		if (ret != 0)
			return (ret);
		vec_ind++;
	}
	return (0);
}
