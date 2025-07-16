/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 12:53:34 by cviel             #+#    #+#             */
/*   Updated: 2025/06/23 18:31:15 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"
#include "ft_vectors.h"

static int	expand_elem(t_vector *dest, char *src, t_minishell mini);

int	expand(t_vector *p_args, t_minishell mini)
{
	int			ret;
	t_vector	copy;
	size_t		i;
	char		*null;

	ft_vector_copy(&copy, p_args);
	ret = ft_vector_init(p_args, copy.capacity, copy.data_size, copy.del);
	if (ret != 0)
		return (ret);
	i = 0;
	while (i < copy.size - 1)
	{
		ret = expand_elem(p_args, ((char **)copy.data)[i], mini);
		if (ret != 0)
		{
			ft_vector_free(&copy);
			return (ret);
		}
		i++;
	}
	null = NULL;
	ft_vector_add_single(p_args, &null);
	ft_vector_free(&copy);
	return (0);
}

int	expand_both(t_vector *p_splitted, t_minishell mini)
{
	int	ret;

	ret = expand_variables(*p_splitted, mini);
	if (ret != 0)
		return (ret);
	return (expand_wildcard(p_splitted));
}

static void	free_exp(t_vector *word)
{
	size_t	i;

	i = 0;
	while (i < word->size)
	{
		free(((t_exp *)word->data)[i].content);
		i++;
	}
	free(word->data);
}

static int	expand_elem(t_vector *dest, char *src, t_minishell mini)
{
	int			ret;
	t_vector	splitted;

	ret = ft_vector_init(&splitted, 5, sizeof(t_exp), free_exp);
	if (ret != 0)
		return (ret);
	ret = split_elem(&splitted, src);
	if (ret != 0)
	{
		ft_vector_free(&splitted);
		return (ret);
	}
	ret = expand_both(&splitted, mini);
	if (ret != 0)
	{
		ft_vector_free(&splitted);
		return (ret);
	}
	ret = rebuild_elem(dest, splitted);
	ft_vector_free(&splitted);
	return (ret);
}
