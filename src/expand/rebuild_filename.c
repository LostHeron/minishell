/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_filename.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-24 12:47:23 by cviel             #+#    #+#             */
/*   Updated: 2025-06-24 12:47:23 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"
#include "expand.h"
#include "ft_vectors.h"
#include "ft_string.h"
#include <stdio.h>

static int	fill_new_name(char *new_name, t_vector splitted, int len);

int	rebuild_filename(t_vector *dest, int ind, t_vector splitted)
{
	int		ret;
	int		len_name;
	char	*new_name;
	size_t	i;

	len_name = 0;
	i = 0;
	while (i < splitted.size)
	{
		len_name += ft_strlen(((t_exp *)splitted.data)[i].content);
		i++;
	}
	new_name = malloc(sizeof(char) * len_name + 1);
	if (new_name == NULL)
		return (ERROR_MALLOC);
	*new_name = 0;
	ret = fill_new_name(new_name, splitted, len_name + 1);
	if (ret != 0)
	{
		free(new_name);
		return (ret);
	}
	free(((t_dirargs *)dest->data)[ind].filename);
	((t_dirargs *)dest->data)[ind].filename = new_name;
	return (0);
}

static int	fill_new_name(char *new_name, t_vector splitted, int len)
{
	size_t	i;
	int		j;

	i = 0;
	while (i < splitted.size)
	{
		if (((t_exp *)splitted.data)[i].quote == NONE)
		{
			j = 0;
			while (((t_exp *)splitted.data)[i].content[j])
			{
				if (((t_exp *)splitted.data)[i].content[j] == ' ')
					return (ERROR_FILENAME);
				j++;
			}
		}
		ft_strlcat(new_name, ((t_exp *)splitted.data)[i].content, len);
		i++;
	}
	return (0);
}
