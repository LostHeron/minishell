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

static int	join_strings(char **first, char *second);
static int	add_unquoted(t_vector *dest, char **string, char *unquoted);

int	rebuild_elem(t_vector *dest, t_vector splitted)
{
	int		ret;
	char	*new_arg;
	size_t	i;

	new_arg = NULL;
	i = 0;
	while (i < splitted.size)
	{
		if (((t_exp *)splitted.data)[i].quote == NONE)
			ret = add_unquoted(dest, &new_arg, ((t_exp *)splitted.data)[i].content);
		else
			ret = join_strings(&new_arg, ((t_exp *)splitted.data)[i].content);
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

static int	join_strings(char **first, char *second)
{
	if (*first == NULL)
		*first = ft_strdup(second);
	else
		*first = ft_strjoin_free_first(*first, second);
	if (*first == NULL)
		return (ERROR_MALLOC);
	return (0);
}

static int	add_tab(t_vector *dest, char **string, char **tab)
{
	int	ret;
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		ret = join_strings(string, tab[i]);
		if (ret != 0)
			return (ret);
		if (tab[i + 1] != NULL)
		{
			ret = ft_vector_add_single(dest, string);
			if (ret != 0)
				return (ret);
			*string = NULL;
		}
		i++;
	}
	return (0);
}

static void	free_tab(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	add_unquoted(t_vector *dest, char **string, char *unquoted)
{
	int		ret;
	char	**unquoted_split;

	if (*unquoted == '\0')
		return (0);
	if (*string != NULL && ft_strchr(WHITE_SPACES, *unquoted) != NULL)
	{
		ret = ft_vector_add_single(dest, string);
		if (ret != 0)
			return (ret);
		*string = NULL;
	}
	unquoted_split = ft_split(unquoted, WHITE_SPACES);
	if (unquoted_split == NULL)
		return (ERROR_MALLOC);
	ret = add_tab(dest, string, unquoted_split);
	free_tab(unquoted_split);
	if (ret != 0)
		return (ret);
	if (*string != NULL && ft_strchr(WHITE_SPACES, unquoted[ft_strlen(unquoted) - 1]) != NULL)
	{
		ret = ft_vector_add_single(dest, string);
		if (ret != 0)
			return (ret);
		*string = NULL;
	}
	return (0);
}
