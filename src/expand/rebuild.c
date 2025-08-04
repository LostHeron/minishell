/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:06:07 by cviel             #+#    #+#             */
/*   Updated: 2025/08/04 17:06:55 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"
#include "ast.h"
#include "ft_vectors.h"
#include "ft_standard.h"
#include "ft_string.h"

int	rebuild_exp(t_vector *dest, t_vector splitted, size_t ind);

int	rebuild_elem(t_vector *dest, t_vector splitted)
{
	int		ret;
	size_t	i;

	i = 0;
	while (i < splitted.size)
	{
		ret = rebuild_exp(dest, splitted, i);
		if (ret != 0)
			return (ret);
		i++;
	}
	return (0);
}

int	rebuild_exp(t_vector *dest, t_vector splitted, size_t ind)
{
	int		ret;
	char	*content;
	size_t	i;

	content = NULL;
	i = 0;
	while (i < (((t_vector *)splitted.data)[ind].size))
	{
		content = ft_strjoin_free_first(content,
				((t_exp *)((t_vector *)splitted.data)[ind].data)[i].content);
		if (content == NULL)
			return (ERROR_MALLOC);
		i++;
	}
	ret = ft_vector_add_single(dest, &content);
	if (ret != 0)
		free(content);
	return (ret);
}

int	rebuild_filename(t_vector *dest, size_t ind, t_vector splitted)
{
	char	*new_name;
	size_t	i;

	if (splitted.size != 1)
		return (ERROR_FILENAME);
	new_name = NULL;
	i = 0;
	while (i < ((*((t_vector *)splitted.data)).size))
	{
		new_name = ft_strjoin_free_first(new_name,
				((t_exp *)(*((t_vector *)splitted.data)).data)[i].content);
		if (new_name == NULL)
			return (ERROR_MALLOC);
		i++;
	}
	free(((t_dirargs *)dest->data)[ind].filename);
	((t_dirargs *)dest->data)[ind].filename = new_name;
	return (0);
}
