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

static int	find_len(t_vector splitted, size_t ind);
static void	fill_arg(char *new_arg, t_vector splitted, size_t *p_ind, int len);

int	rebuild_elem(t_vector *dest, t_vector splitted)
{
	int		ret;
	char	*new_arg;
	int		len_arg;
	size_t	i;

	i = 0;
	while (i < splitted.size)
	{
		len_arg = find_len(splitted, i);
		if (len_arg > 0)
		{
			new_arg = ft_calloc(len_arg + 1, sizeof(char));
			if (new_arg == NULL)
				return (ERROR_MALLOC);
			fill_arg(new_arg, splitted, &i, len_arg);
			ret = ft_vector_add_single(dest, &new_arg);
			if (ret != 0)
			{
				free(new_arg);
				return (ret);
			}
		}
	}
	return (0);
}

static void	skip_charset(char *s, char *charset, int *p_ind)
{
	while (s[*p_ind] != '\0' && ft_strchr(charset, s[*p_ind]) != NULL)
		(*p_ind)++;
}

static int	find_len(t_vector splitted, size_t ind)
{
	int			len;
	static int	i;

	len = 0;
	while (ind < splitted.size)
	{
		if (((t_exp *)splitted.data)[ind].quote == NONE)
		{
			while (((t_exp *)splitted.data)[ind].content[i])
			{
				if (ft_strchr(WHITE_SPACES, ((t_exp *)splitted.data)[ind].content[i]) != NULL)
				{
					skip_charset(((t_exp *)splitted.data)[ind].content, WHITE_SPACES, &i);
					return (len);
				}
				len++;
				i++;
			}
			i = 0;
		}
		else
			len += ft_strlen(((t_exp *)splitted.data)[ind].content);
		ind++;
	}
	return (len);
}

static void	fill_arg(char *new_arg, t_vector splitted, size_t *p_ind, int len)
{
	int			len_copy;
	static int	i;

	len_copy = 0;
	while (*p_ind < splitted.size)
	{
		if (((t_exp *)splitted.data)[*p_ind].quote == NONE)
		{
			while (((t_exp *)splitted.data)[*p_ind].content[i])
			{
				if (ft_strchr(WHITE_SPACES, ((t_exp *)splitted.data)[*p_ind].content[i]))
				{
					skip_charset(((t_exp *)splitted.data)[*p_ind].content, WHITE_SPACES, &i);
					return ;
				}
				new_arg[len_copy] = ((t_exp *)splitted.data)[*p_ind].content[i];
				len_copy++;
				i++;
			}
			i = 0;
		}
		else
			len_copy = ft_strlcat(new_arg, ((t_exp *)splitted.data)[*p_ind].content, len);
		(*p_ind)++;
	}
}
