/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-30 13:27:31 by cviel             #+#    #+#             */
/*   Updated: 2025-06-30 13:27:31 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "expand.h"
#include "ft_vectors.h"
#include "ft_lists_single.h"
#include "ft_string.h"
#include <stdio.h>

static int	expand_here(t_vector *p_splitted, int *p_vec_ind, int *p_ind);
static int	expand_single(t_vector *p_splitted, size_t *p_vec_ind);

int	expand_wildcard(t_vector *p_splitted)
{
	int		ret;
	size_t	i;

	i = 0;
	while ((size_t)i < p_splitted->size)
	{
		if (((t_exp *)p_splitted->data)[i].quote != SINGLE)
		{
			ret = expand_single(p_splitted, &i);
			if (ret != 0)
				return (ret);
		}
		i++;
	}
	return (0);
}

static int	expand_single(t_vector *p_splitted, size_t *p_vec_ind)
{
	int		ret;
	size_t	i;

	i = 0;
	while ((*p_vec_ind) < p_splitted->size
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

static void	pattern_start(t_vector splitted, size_t *p_vec_ind, int *p_ind)
{
	while (*p_vec_ind >= 0)
	{
		if (((t_exp *)splitted.data)[*p_vec_ind].quote == NONE)
		{
			if (*p_ind == -1)
				*p_ind = ft_strlen(((t_exp *)splitted.data)[*p_vec_ind].content) - 1;
			while (*p_ind >= 0)
			{
				if (ft_strchr(WHITE_SPACES,
						((t_exp *)splitted.data)[*p_vec_ind].content[*p_ind])
						!= NULL)
				{
					(*p_ind)++;
					return ;
				}
				(*p_ind)--;
			}
		}
		(*p_vec_ind)--;
	}
	if (*p_vec_ind < 0)
	{
		*p_vec_ind = 0;
		*p_ind = 0;
	}
}

static int	add_elem(t_vector *p_pattern, t_exp exp_part, int ind)
{
	t_pat	elem;

	elem.c = exp_part.content[ind];
	if (elem.c == '*' && exp_part.quote == NONE)
		elem.wild = TRUE;
	else
		elem.wild = FALSE;
	return (ft_vector_add_single(p_pattern, &elem));
}

static int	get_pattern(t_vector *p_pattern, t_vector splitted,
				int vec_ind, int ind)
{
	int		ret;

	ret = ft_vector_init(p_pattern, 5, sizeof(t_pat), free_data);
	if (ret != 0)
		return (ret);
	while ((size_t)vec_ind < splitted.size)
	{
		if (((t_exp *)splitted.data)[vec_ind].quote == NONE
			&& ft_strchr(WHITE_SPACES,
			((t_exp *)splitted.data)[vec_ind].content[ind]))
			return (0);
		else
		{
			ret = add_elem(p_pattern, ((t_exp *)splitted.data)[vec_ind], ind);
			if (ret != 0)
				return (ret);
			ind++;
			if (((t_exp *)splitted.data)[vec_ind].content[ind] == '\0')
				vec_ind++;
		}
	}
	return (0);
}

static int	init_replace(t_vector *p_splitted, t_vector *p_copy, int vec_ind)
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

static int	end_replace(t_vector *p_splitted, t_vector copy, int vec_ind)
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

static int	handle_wildcard(t_vector *p_splitted, int *p_vec_ind,
				int *p_ind, char *replace)
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

static int	expand_here(t_vector *p_splitted, int *p_vec_ind, int *p_ind)
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
		*p_ind += 1;
		return (ret);
	}
	ft_vector_free(&pattern);
	ret = handle_wildcard(p_splitted, p_vec_ind, p_ind, replace);
	free(replace);
	return (ret);
}
