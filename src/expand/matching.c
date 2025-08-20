/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matching.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:53:48 by cviel             #+#    #+#             */
/*   Updated: 2025/08/20 19:15:19 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "expand.h"
#include "ft_vectors.h"
#include "ft_string.h"

static int	build_segment(char **seg, t_vector pattern, size_t *ind);
static int	matching_start(t_vector pattern, char **p_elem,
				char *match, size_t *ind);
static void	matching_segment(char **p_elem, char **seg, char *p_match);
static void	matching_end(char *elem, char *seg, char *p_match);

/*	matching_start -> OK
	build_segment -> OK
*/
int	matching(t_vector pattern, char *elem, char *p_match)
{
	int		ret;
	char	*seg;
	size_t	i;

	i = 0;
	ret = matching_start(pattern, &elem, p_match, &i);
	if (ret != 0 || *p_match == FALSE)
		return (ret);
	seg = NULL;
	while (i < pattern.size)
	{
		ret = build_segment(&seg, pattern, &i);
		if (ret != 0 || seg == NULL)
			return (ret);
		if (i < pattern.size)
		{
			matching_segment(&elem, &seg, p_match);
			if (*p_match == FALSE)
				return (0);
		}
	}
	if (seg != NULL)
		matching_end(elem, seg, p_match);
	free(seg);
	return (0);
}

/*	malloc -> OK
	ft_strjoin_free_first -> OK
*/
static int	build_segment(char **seg, t_vector pattern, size_t *ind)
{
	char	*join;

	while (*ind < pattern.size
		&& ((t_pat *)pattern.data)[*ind].wild == TRUE)
		(*ind)++;
	while (*ind < pattern.size
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
		(*ind)++;
	}
	return (0);
}

/*	build_segment -> OK */
static int	matching_start(t_vector pattern,
	char **p_elem, char *match, size_t *ind)
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

static void	matching_segment(char **p_elem, char **seg, char *p_match)
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

static void	matching_end(char *elem, char *seg, char *p_match)
{
	int	len_elem;
	int	len_seg;

	len_elem = ft_strlen(elem);
	len_seg = ft_strlen(seg);
	if (len_elem < len_seg || ft_strcmp(&elem[len_elem - len_seg], seg) != 0)
		*p_match = FALSE;
}
