/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-23 14:06:07 by cviel             #+#    #+#             */
/*   Updated: 2025/06/23 18:35:47 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"
#include "ft_vectors.h"
#include "ft_standard.h"
#include "ft_string.h"

static int	split_and_fill(t_vector *dest, t_exp exp);

int	rebuild_elem(t_vector *dest, t_vector splitted)
{
	int		ret;
	size_t	i;
	char	*str_copy;

	i = 0;
	while (i < splitted.size)
	{
		if (((t_exp *)splitted.data)[i].quote == NONE)
		{
			ret = split_and_fill(dest, ((t_exp *)splitted.data)[i]);
			if (ret != 0)
				return (ret);
		}
		else
		{
			str_copy = ft_strdup(((t_exp *)splitted.data)[i].content);
			if (str_copy == NULL)
				return (ERROR_MALLOC);
			ret = ft_vector_add_single(dest, &str_copy);
			if (ret != 0)
				return (ret);
		}
		i++;
	}
	return (0);
}

static void	free_tab(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	split_and_fill(t_vector *dest, t_exp exp)
{
	int		ret;
	char	**arr;
	int		i;

	arr = ft_split(exp.content, WHITE_SPACES);
	if (arr == NULL)
		return (ERROR_MALLOC);
	i = 0;
	while (arr[i] != NULL)
	{
		ret = ft_vector_add_single(dest, arr + i);
		if (ret != 0)
		{
			free_tab(arr);
			return (ret);
		}
		i++;
	}
	return (0);
}
