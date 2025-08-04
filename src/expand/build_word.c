/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:31:56 by cviel             #+#    #+#             */
/*   Updated: 2025/08/04 16:14:44 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"
#include "ft_vectors.h"
#include "ft_string.h"

static int	add_to_word(t_vector *p_word, t_vector copy,
				size_t *p_vec_ind, size_t *p_ind);

int	build_word(t_vector *p_splitted, t_vector copy,
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

static void	skip_charset(char *charset, t_vector elem,
				size_t *p_vec_ind, size_t *p_ind)
{
	while (((t_exp *)elem.data)[*p_vec_ind].content[*p_ind] != '\0'
			&& ft_strchr(charset,
			((t_exp *)elem.data)[*p_vec_ind].content[*p_ind]) != NULL)
		(*p_ind)++;
	if (((t_exp *)elem.data)[*p_vec_ind].content[*p_ind] == '\0')
	{
		(*p_vec_ind)++;
		*p_ind = 0;
	}
}

static int	fill_exp(t_exp *p_exp, char *content, size_t *p_ind)
{
	size_t	i;

	i = 0;
	while (content[*p_ind + i] != '\0'
		&& ft_strchr(WHITE_SPACES, content[*p_ind + i]) == NULL)
		i++;
	if (i == 0)
		return (0);
	p_exp->content = ft_strndup(&content[*p_ind], i);
	if (p_exp->content == NULL)
		return (ERROR_MALLOC);
	*p_ind += i;
	return (0);
}

static int	unquoted_split(t_vector *p_word, t_vector copy,
				size_t *p_vec_ind, size_t *p_ind)
{
	int		ret;
	t_exp	exp;

	exp.quote = NONE;
	exp.content = NULL;
	ret = fill_exp(&exp, ((t_exp *)
				copy.data)[*p_vec_ind].content, p_ind);
	if (exp.content == NULL)
		return (ret);
	ret = ft_vector_add_single(p_word, &exp);
	if (ret != 0)
		free(exp.content);
	return (ret);
}

static int	add_to_word(t_vector *p_word, t_vector copy,
				size_t *p_vec_ind, size_t *p_ind)
{
	int	ret;

	ret = 0;
	while (ret == 0 && *p_vec_ind < copy.size)
	{
		if (((t_exp *)copy.data)[*p_vec_ind].quote == NONE)
		{
			ret = unquoted_split(p_word, copy, p_vec_ind, p_ind);
			if (((t_exp *)copy.data)[*p_vec_ind].content[*p_ind] != '\0'
				&& ft_strchr(WHITE_SPACES,
					((t_exp *)copy.data)[*p_vec_ind].content[*p_ind]) != NULL)
			{
				skip_charset(WHITE_SPACES, copy, p_vec_ind, p_ind);
				break ;
			}
		}
		else
			ret = ft_vector_add_single(p_word,
					&((t_exp *)copy.data)[*p_vec_ind]);
		(*p_vec_ind)++;
		(*p_ind) = 0;
	}
	return (ret);
}
