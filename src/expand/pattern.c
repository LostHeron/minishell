/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-17 14:19:36 by cviel             #+#    #+#             */
/*   Updated: 2025-07-17 14:19:36 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "expand.h"
#include "ft_vectors.h"
#include "ft_string.h"

static int	add_elem(t_vector *p_pattern, t_exp exp_part, ssize_t ind);

void	pattern_start(t_vector splitted,
				ssize_t *p_vec_ind, ssize_t *p_ind)
{
	while (*p_vec_ind >= 0)
	{
		if (((t_exp *)splitted.data)[*p_vec_ind].quote == NONE)
		{
			if (*p_ind == -1)
				*p_ind = ft_strlen(((t_exp *)
							splitted.data)[*p_vec_ind].content) - 1;
			while (*p_ind >= 0)
			{
				if (ft_strchr(WHITE_SPACES, ((t_exp *)
							splitted.data)[*p_vec_ind].content[*p_ind]) != NULL)
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

int	get_pattern(t_vector *p_pattern, t_vector splitted,
				ssize_t vec_ind, ssize_t ind)
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

static int	add_elem(t_vector *p_pattern, t_exp exp_part, ssize_t ind)
{
	t_pat	elem;

	elem.c = exp_part.content[ind];
	if (elem.c == '*' && exp_part.quote == NONE)
		elem.wild = TRUE;
	else
		elem.wild = FALSE;
	return (ft_vector_add_single(p_pattern, &elem));
}
