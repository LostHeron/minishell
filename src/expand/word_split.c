/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:09:17 by cviel             #+#    #+#             */
/*   Updated: 2025/08/01 00:33:37 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "expand.h"
#include "ft_vectors.h"
#include "ft_string.h"
#include "ft_memory.h"

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
