/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-25 15:24:05 by cviel             #+#    #+#             */
/*   Updated: 2025-06-25 15:24:05 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"
#include "expand.h"
#include "ft_vectors.h"

static int	expand_filename(t_vector *p_redir, int ind,
				char *src, t_minishell mini);

int	expand_redir(t_vector *p_redir, t_minishell mini)
{
	int			ret;
	size_t		i;

	i = 0;
	while (i < p_redir->size)
	{
		ret = expand_filename(p_redir, i,
				((t_dirargs *)p_redir->data)[i].filename, mini);
		if (ret != 0)
		{
			ft_vector_free(p_redir);
			return (ret);
		}
		i++;
	}
	return (0);
}

static int	expand_filename(t_vector *dest, int ind,
			char *src, t_minishell mini)
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
	ret = rebuild_filename(dest, ind, splitted);
	ft_vector_free(&splitted);
	return (ret);
}
