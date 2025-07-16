/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matching.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-16 15:53:48 by cviel             #+#    #+#             */
/*   Updated: 2025-07-16 15:53:48 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "expand.h"
#include "ft_vectors.h"
#include "ft_string.h"

static int	build_segment(char **seg, t_vector pattern, int *ind);
static int	pattern_start(t_vector pattern, char **p_elem,
				int *match, int *ind);
static void	segment_matching(char **p_elem, char **seg, int *p_match);

int	matching(t_vector pattern, char *elem, int *p_match)
{
	int		ret;
	char	*s;
	int		i;

	i = 0;
	ret = pattern_start(pattern, &elem, p_match, &i);
	if (ret != 0 || *p_match == FALSE)
		return (ret);
	s = NULL;
	while ((size_t)i < pattern.size)
	{
		ret = build_segment(&s, pattern, &i);
		if (ret != 0 || s == NULL)
			return (ret);
		if ((size_t)i < pattern.size)
		{
			segment_matching(&elem, &s, p_match);
			if (*p_match == FALSE)
				return (0);
		}
	}
	if (s != NULL && ft_strcmp(&elem[ft_strlen(elem) - ft_strlen(s)], s) != 0)
		*p_match = FALSE;
	free(s);
	return (0);
}

static int	build_segment(char **seg, t_vector pattern, int *ind)
{
	char	*join;

	while ((size_t)(*ind) < pattern.size
		&& ((t_pat *)pattern.data)[*ind].wild == TRUE)
		(*ind) += 1;
	while ((size_t)(*ind) < pattern.size
		&& ((t_pat *)pattern.data)[*ind].wild == FALSE)
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

static int	pattern_start(t_vector pattern, char **p_elem, int *match, int *ind)
{
	int		ret;
	char	*seg;

	if (*p_elem[0] == '.' && ((t_pat *)pattern.data)[0].c != '.')
	{
		*match = FALSE;
		return (0);
	}
	seg = NULL;
	if (((t_pat *)pattern.data)[0].wild == FALSE)
	{
		ret = build_segment(&seg, pattern, ind);
		if (ret != 0)
			return (ret);
		if (ft_strncmp(*p_elem, seg, ft_strlen(seg)) != 0)
		{
			free(seg);
			*match = FALSE;
			return (0);
		}
		*p_elem += ft_strlen(seg);
		free(seg);
		seg = NULL;
	}
	return (0);
}

static void	segment_matching(char **p_elem, char **seg, int *p_match)
{
	*p_elem = ft_strstr(*p_elem, *seg);
	if (*p_elem == NULL)
	{
		free(*seg);
		*p_match = FALSE;
		return ;
	}
	*p_elem += ft_strlen(*seg);
	free(*seg);
	*seg = NULL;
	return ;
}
