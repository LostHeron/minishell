/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:10:14 by cviel             #+#    #+#             */
/*   Updated: 2025/08/07 18:19:39 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ast.h"
#include "ft_memory.h"

t_ast	*create_leaf(t_type type);

t_ast	*create_ast(t_vector tokens, t_prio max_prio, size_t *ind)
{
	int		ret;
	t_type	type;
	t_ast	*root;

	type = get_type(tokens, *ind);
	root = create_leaf(type);
	if (!root)
		return (NULL);
	while (get_prio(type) < max_prio)
	{
		if (type == SUBSHELL)
			ret = create_subshell(&root->arguments.sub_args, tokens, ind);
		else if (type == COMMAND)
			ret = fill_command(&root->arguments.com_args, tokens, ind);
		else
			ret = create_operator(&root, type, tokens, ind);
		if (ret != 0)
		{
			free_tree(&root);
			return (NULL);
		}
		type = get_type(tokens, *ind);
	}
	return (root);
}

static int	init_vectors(t_vector *dir_args, t_vector *content)
{
	int	ret;

	ft_bzero(dir_args, sizeof(t_vector));
	ret = ft_vector_init(dir_args, 5, sizeof(t_dirargs), free_dirargs);
	if (ret != 0)
		return (ret);
	return (ft_vector_init(content, 5, sizeof(char *), free_command_content));
}

t_ast	*create_leaf(t_type type)
{
	t_ast	*leaf;

	leaf = malloc(sizeof(t_ast));
	if (!leaf)
		return (NULL);
	leaf->type = type;
	if (type == COMMAND)
	{
		if (init_vectors(&leaf->arguments.com_args.dir_args,
				&leaf->arguments.com_args.content))
		{
			ft_vector_free(&leaf->arguments.com_args.dir_args);
			return (NULL);
		}
	}
	else if (type == SUBSHELL)
	{
		if (ft_vector_init(&leaf->arguments.sub_args.dir_args,
				5, sizeof(t_dirargs), free_dirargs))
		{
			free(leaf);
			return (NULL);
		}
	}
	return (leaf);
}
