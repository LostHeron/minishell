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

static int	rebuild_exp(t_vector *dest, t_vector splitted,
				size_t ind, char **p_new_arg);
static int	add_unquoted(t_vector *dest, char **p_string, char *unquoted);

int	rebuild_elem(t_vector *dest, t_vector splitted)
{
	int		ret;
	char	*new_arg;
	size_t	i;

	new_arg = NULL;
	i = 0;
	while (i < splitted.size)
	{
		ret = rebuild_exp(dest, splitted, i, &new_arg);
		if (ret != 0)
		{
			free(new_arg);
			return (ret);
		}
		i++;
	}
	if (new_arg != NULL)
	{
		ret = ft_vector_add_single(dest, &new_arg);
		if (ret != 0)
			free(new_arg);
	}
	return (ret);
}

static int	rebuild_exp(t_vector *dest, t_vector splitted,
				size_t ind, char **p_new_arg)
{
	int	ret;

	if (((t_exp *)splitted.data)[ind].quote == NONE)
	{
		ret = add_unquoted(dest, p_new_arg,
				((t_exp *)splitted.data)[ind].content);
		return (ret);
	}
	else
	{
		*p_new_arg = ft_strjoin_free_first(*p_new_arg,
				((t_exp *)splitted.data)[ind].content);
		if (*p_new_arg == NULL)
			return (ERROR_MALLOC);
		return (0);
	}
}

static int	add_tab(t_vector *dest, char **p_string, char **tab)
{
	int	ret;
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		*p_string = ft_strjoin_free_first(*p_string, tab[i]);
		if (*p_string == NULL)
			return (ERROR_MALLOC);
		if (tab[i + 1] != NULL)
		{
			ret = ft_vector_add_single(dest, p_string);
			if (ret != 0)
				return (ret);
			*p_string = NULL;
		}
		i++;
	}
	return (0);
}

static int	whitespace_check(t_vector *dest, char **p_string,
				char *unquoted, int ind)
{
	int	ret;

	if (*p_string != NULL && ft_strchr(WHITE_SPACES, unquoted[ind]) != NULL)
	{
		ret = ft_vector_add_single(dest, p_string);
		if (ret != 0)
			return (ret);
		*p_string = NULL;
	}
	return (0);
}

static int	add_unquoted(t_vector *dest, char **p_string, char *unquoted)
{
	int		ret;
	char	**unquoted_split;

	if (*unquoted == '\0')
		return (0);
	ret = whitespace_check(dest, p_string, unquoted, 0);
	if (ret != 0)
		return (ret);
	unquoted_split = ft_split(unquoted, WHITE_SPACES);
	if (unquoted_split == NULL)
		return (ERROR_MALLOC);
	ret = add_tab(dest, p_string, unquoted_split);
	free_tab(unquoted_split);
	if (ret != 0)
		return (ret);
	ret = whitespace_check(dest, p_string, unquoted, ft_strlen(unquoted) - 1);
	return (ret);
}
