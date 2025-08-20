/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:53:34 by cviel             #+#    #+#             */
/*   Updated: 2025/08/19 18:43:03 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "minishell.h"
#include "expand.h"
#include "ft_vectors.h"
#include "ft_memory.h"

static int	expand_everything(t_vector *p_args,
				t_vector copy, t_minishell mini);
static int	expand_elem(t_vector *dest, char *src, t_minishell mini);

/* ft_vector_init fail : TO DO ;
 * expand_everything fail : TO DO ;
 * ft_vector_add_single : TO DO ;
*/
int	expand(t_vector *p_args, t_minishell mini)
{
	int			ret;
	t_vector	copy;
	char		*null;
	//static int a;

	//printf("a = %i\n", a);
	//a++;
	ft_vector_copy(&copy, p_args);
	ft_bzero(p_args, sizeof(t_vector));
	/*
	ret = ERROR_MALLOC;
	if (a < 3)
	*/
	ret = ft_vector_init(p_args, copy.capacity, copy.data_size, copy.del);
	if (ret != 0)
	{
		ft_vector_free(&copy);
		return (ret);
	}
	ret = expand_everything(p_args, copy, mini);
	ft_vector_free(&copy);
	if (ret != 0)
		return (ret);
	null = NULL;
	return (ft_vector_add_single(p_args, &null));
}

/*	expand_variables -> OK
	word_split -> OK */
int	expand_all(t_vector *p_splitted, t_minishell mini)
{
	int	ret;
	
	ret = expand_variables(*p_splitted, mini);
	if (ret != 0)
		return (ret);
	ret = word_split(p_splitted);
	if (ret != 0)
		return (ret);
	return (expand_wildcard(p_splitted));
}

static int	expand_everything(t_vector *p_args, t_vector copy, t_minishell mini)
{
	int		ret;
	size_t	i;

	i = 0;
	while (i < copy.size - 1)
	{
		ret = expand_elem(p_args, ((char **)copy.data)[i], mini);
		if (ret != 0)
		{
			return (ret);
		}
		i++;
	}
	return (0);
}

/* ft_vector_init fail : OK !*/
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
	ret = expand_all(&splitted, mini);
	if (ret != 0)
	{
		ft_vector_free(&splitted);
		return (ret);
	}
	ret = rebuild_elem(dest, splitted);
	ft_vector_free(&splitted);
	return (ret);
}
