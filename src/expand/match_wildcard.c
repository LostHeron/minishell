/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:00:35 by cviel             #+#    #+#             */
/*   Updated: 2025/08/05 18:41:35 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include "minishell.h"
#include "expand.h"
#include "ast.h"
#include "ft_vectors.h"
#include "ft_string.h"
#include "ft_memory.h"

static int	match_and_link(t_vector *p_names, t_vector pattern, char *name);
static int	get_next_dir(DIR *dir, struct dirent **elem);

int	find_match(t_vector *p_names, t_vector pattern)
{
	int				ret;
	DIR				*dir;
	struct dirent	*elem;

	ft_bzero(p_names, sizeof(t_vector));
	ret = ft_vector_init(p_names, 5, sizeof(char *), free_command_content);
	if (ret != 0)
		return (ret);
	dir = opendir(".");
	if (dir == NULL)
	{
		perror("opendir");
		return (1);
	}
	ret = get_next_dir(dir, &elem);
	while (ret == 0 && elem != NULL)
	{
		ret = match_and_link(p_names, pattern, elem->d_name);
		if (ret != 0)
			break ;
		ret = get_next_dir(dir, &elem);
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

static int	match_and_link(t_vector *p_names, t_vector pattern, char *name)
{
	int		ret;
	char	*content;
	char	match;

	match = TRUE;
	ret = matching(pattern, name, &match);
	if (ret != 0 || match == FALSE)
		return (ret);
	content = ft_strdup(name);
	if (content == NULL)
		return (ERROR_MALLOC);
	ret = ft_vector_add_single(p_names, &content);
	if (ret != 0)
		free(content);
	return (ret);
}
