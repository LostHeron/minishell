/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-03 13:00:35 by cviel             #+#    #+#             */
/*   Updated: 2025-07-03 13:00:35 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include "minishell.h"
#include "expand.h"
#include "ft_vectors.h"
#include "ft_lists_single.h"
#include "ft_string.h"

static int	matching(t_vector pattern, char *elem_name, int *match);

int	find_match(char **replace, t_vector pattern)
{
	int				ret;
	DIR 			*dir;
	struct dirent	*elem;
	int				match;

	dir = opendir(".");
	if (dir == NULL)
	{
		perror("opendir");
		return (1);
	}
	errno = 0;
	elem = readdir(dir);
	if (errno != 0)
	{
		closedir(dir);
		perror("readdir");
		return (1);
	}
	while (elem != NULL)
	{
		match = FALSE;
		ret = matching(pattern, elem->d_name, &match);
		if (ret != 0)
		{
			closedir(dir);
			return (ret);
		}
		if (match == TRUE)
		{
			if (*replace != NULL)
			{
				*replace = ft_strjoin_free_first(*replace, " ");
				if (*replace == NULL)
				{
					closedir(dir);
					return (ERROR_MALLOC);
				}
			}
			*replace = ft_strjoin_free_first(*replace, elem->d_name);
			if (*replace == NULL)
			{
				closedir(dir);
				return (ERROR_MALLOC);
			}
		}
		errno = 0;
		elem = readdir(dir);
		if (errno != 0)
		{
			closedir(dir);
			perror("readdir");
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

static int	build_segment(char **seg, t_vector pattern, int *ind)
{
	char	*join;
	
	while ((size_t)(*ind) < pattern.size && ((t_pat *)pattern.data)[*ind].wild == TRUE)
		(*ind) += 1;
	while ((size_t)(*ind) < pattern.size && ((t_pat *)pattern.data)[*ind].wild == FALSE)
	{
		join = malloc(sizeof(char) * 2);
		if (join == NULL)
			return (ERROR_MALLOC);
		join[0] = ((t_pat *)pattern.data)[*ind].c;
		join[1] = '\0';
		*seg = ft_strjoin_free_first(*seg, join);
		free(join);
		if (*seg == NULL)
			return (ERROR_MALLOC);
		(*ind) += 1;
	}
	return (0);
}

static int	matching(t_vector pattern, char *elem_name, int *match)
{
	int		ret;
	char	*seg;
	int		i;

	seg = NULL;
	i = 0;
	if (((t_pat *)pattern.data)[i].wild == FALSE)
	{
		ret = build_segment(&seg, pattern, &i);
		if (ret != 0)
			return (ret);
		if (ft_strncmp(elem_name, seg, ft_strlen(seg)) != 0)
		{
			free(seg);
			return (0);
		}
		elem_name += ft_strlen(seg);
		free(seg);
		seg = NULL;
	}
	while ((size_t)i < pattern.size)
	{
		ret = build_segment(&seg, pattern, &i);
		if (ret != 0)
			return (ret);
		if (seg == NULL)
		{
			*match = TRUE;
			return (0);
		}
		if ((size_t)i < pattern.size)
		{
			elem_name = ft_strstr(elem_name, seg);
			if (elem_name == NULL)
			{
				free(seg);
				return (0);
			}
			elem_name += ft_strlen(seg);
			free(seg);
			seg = NULL;
		}
	}
	if (seg != NULL)
	{
		if (ft_strcmp(&elem_name[ft_strlen(elem_name) - ft_strlen(seg)], seg) != 0)
		{
			free(seg);
			return (0);
		}
		free(seg);
	}
	*match = TRUE;
	return (0);
}
