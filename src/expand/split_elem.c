/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-23 12:59:18 by cviel             #+#    #+#             */
/*   Updated: 2025/06/23 18:32:35 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"
#include "ft_vectors.h"
#include "ft_string.h"

static int	fill_exp(t_exp *p_exp_part, char *src, int *p_ind);
static int	fill_content(t_exp *p_exp_part, char *src, int *p_ind, char *charset);
static int	is_charset(char c, char *set);

int	split_elem(t_vector *splitted, char *src)
{
	int		ret;
	t_exp	exp_part;
	int		i;

	i = 0;
	while (src[i])
	{
		ret = fill_exp(&exp_part, src, &i);
		if (ret != 0)
			return (ret);
		ret = ft_vector_add_single(splitted, &exp_part);
		if (ret != 0)
		{
			free(exp_part.content);
			return (ret);
		}
	}
	return (0);
}

static int	fill_exp(t_exp *p_exp_part, char *src, int *p_ind)
{
	if (src[*p_ind] == '\'')
	{
		p_exp_part->quote = SINGLE;
		(*p_ind)++;
		return (fill_content(p_exp_part, src, p_ind, "'"));
	}
	else if (src[*p_ind] == '"')
	{
		p_exp_part->quote = DOUBLE;
		(*p_ind)++;
		return (fill_content(p_exp_part, src, p_ind, "\""));
	}
	else
	{
		p_exp_part->quote = NONE;
		return (fill_content(p_exp_part, src, p_ind, "'\""));
	}
}

static int	fill_content(t_exp *p_exp_part, char *src, int *p_ind, char *charset)
{
	int	i;

	i = 0;
	while (src[*p_ind + i] && (is_charset(src[*p_ind + i], charset) == 0))
		i++;
	p_exp_part->content = ft_strndup(src + *p_ind, i);
	if (p_exp_part->content == NULL)
		return (ERROR_MALLOC);
	*p_ind += i;
	if (src[*p_ind])
		(*p_ind)++;
	return (0);
}

static int	is_charset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}
