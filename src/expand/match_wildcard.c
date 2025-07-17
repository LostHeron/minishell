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

#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include "minishell.h"
#include "expand.h"
#include "ft_vectors.h"
#include "ft_string.h"

static int	match_and_join(char **replace, t_vector pattern, char *name);
static int	get_next_dir(DIR *dir, struct dirent **elem);

int	find_match(char **replace, t_vector pattern)
{
	int				ret;
	DIR				*dir;
	struct dirent	*elem;

	dir = opendir(".");
	if (dir == NULL)
	{
		perror("opendir");
		return (1);
	}
	ret = get_next_dir(dir, &elem);
	while (elem != NULL)
	{
		ret = match_and_join(replace, pattern, elem->d_name);
		if (ret != 0)
			break ;
		ret = get_next_dir(dir, &elem);
		if (ret != 0)
			break ;
	}
	if (closedir(dir) == -1)
		perror("closedir");
	return (ret);
}

static int	get_next_dir(DIR *dir, struct dirent **elem)
{
	errno = 0;
	*elem = readdir(dir);
	if (errno != 0)
	{
		perror("readdir");
		return (1);
	}
	return (0);
}

static int	match_and_join(char **replace, t_vector pattern, char *name)
{
	int	ret;
	int	match;

	match = TRUE;
	ret = matching(pattern, name, &match);
	if (ret != 0)
		return (ret);
	if (match == TRUE)
	{
		if (*replace != NULL)
		{
			*replace = ft_strjoin_free_first(*replace, " ");
			if (*replace == NULL)
				return (ERROR_MALLOC);
		}
		*replace = ft_strjoin_free_first(*replace, name);
		if (*replace == NULL)
			return (ERROR_MALLOC);
	}
	return (0);
}
