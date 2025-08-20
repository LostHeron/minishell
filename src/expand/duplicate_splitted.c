/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_splitted.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:17:58 by cviel             #+#    #+#             */
/*   Updated: 2025/08/20 17:29:36 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "ft_vectors.h"
#include "ft_string.h"

static int	duplicate_word(t_vector *p_word_dest, t_vector word_src);

int	duplicate_splitted(t_vector *p_dest, t_vector src)
{
	t_vector	word;
	int			ret;

	ret = ft_vector_init(&word, 5, sizeof(t_exp), free_exp);
	if (ret != 0)
		return (ret);
	ret = duplicate_word(&word, src);
	if (ret != 0)
	{
		ft_vector_free(&word);
		return (ret);
	}
	ret = ft_vector_add_single(p_dest, &word);
	if (ret != 0)
	{
		ft_vector_free(&word);
		return (ret);
	}
	return (0);
}

static int	duplicate_word(t_vector *p_word_dest, t_vector word_src)
{
	t_exp	exp;
	size_t	i;
	int		ret;

	i = 0;
	while (i < word_src.size)
	{
		exp.quote = ((t_exp *)word_src.data)[i].quote;
		exp.content = ft_strdup(((t_exp *)word_src.data)[i].content);
		if (exp.content == NULL)
			return (ERROR_MALLOC);
		ret = ft_vector_add_single(p_word_dest, &exp);
		if (ret != 0)
		{
			free(exp.content);
			return (ret);
		}
		i++;
	}
	return (0);
}
