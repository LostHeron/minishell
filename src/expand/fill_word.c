/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:47:39 by cviel             #+#    #+#             */
/*   Updated: 2025/08/19 18:40:19 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "expand.h"
#include "ft_vectors.h"
#include "ft_string.h"

static void	skip_charset(char *charset, t_vector elem,
				size_t *p_vec_ind, size_t *p_ind);
static int	add_unquoted(t_vector *p_word, t_vector copy,
				size_t *p_vec_ind, size_t *p_ind);
static int	add_quoted(t_vector *p_word, t_exp elem);

/*	add_unquoted -> OK
	add_quoted -> OK */
int	fill_word(t_vector *p_word, t_vector copy,
	size_t *p_vec_ind, size_t *p_ind)
{
	int	ret;

	ret = 0;
	while (ret == 0 && *p_vec_ind < copy.size)
	{
		if (((t_exp *)copy.data)[*p_vec_ind].quote == NONE)
		{
			ret = add_unquoted(p_word, copy, p_vec_ind, p_ind);
			if (((t_exp *)copy.data)[*p_vec_ind].content[*p_ind] != '\0'
				&& ft_strchr(WHITE_SPACES,
					((t_exp *)copy.data)[*p_vec_ind].content[*p_ind]) != NULL)
			{
				skip_charset(WHITE_SPACES, copy, p_vec_ind, p_ind);
				break ;
			}
		}
		else
			ret = add_quoted(p_word,
					((t_exp *)copy.data)[*p_vec_ind]);
		(*p_vec_ind)++;
		(*p_ind) = 0;
	}
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

/*	ft_strndup -> OK */
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

/*	fill_exp -> OK
	ft_vector_add_single -> OK */
static int	add_unquoted(t_vector *p_word, t_vector copy,
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

/*	ft_strndup -> OK
	ft_vector_add_single -> OK */
static int	add_quoted(t_vector *p_word, t_exp elem)
{
	int		ret;
	t_exp	exp;

	exp.quote = elem.quote;
	exp.content = ft_strdup(elem.content);
	if (exp.content == NULL)
		return (ERROR_MALLOC);
	ret = ft_vector_add_single(p_word, &exp);
	if (ret != 0)
		free(exp.content);
	return (ret);
}
