/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-21 13:10:14 by cviel             #+#    #+#             */
/*   Updated: 2025-07-21 13:10:14 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ast.h"
#include "ft_string.h"
#include "ft_standard.h"
#include "ft_memory.h"

static t_ast	*create_leaf(t_type type);
static int		create_subshell(t_subargs *p_sub_args,
					t_vector tokens, size_t *ind);
static int		create_operator(t_ast **p_root, t_type type,
					t_vector tokens, size_t *ind);

t_ast	*create_ast(t_vector tokens, t_type max_prio, size_t *ind)
{
	int		ret;
	t_type	type;
	t_ast	*root;

	type = get_type(tokens, *ind);
	root = create_leaf(type);
	if (!root)
		return (NULL);
	while (type < max_prio)
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

static t_ast	*create_leaf(t_type type)
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

static int	create_subshell(t_subargs *p_sub_args, t_vector tokens, size_t *ind)
{
	t_dir	dir;

	(*ind)++;
	p_sub_args->sub = create_ast(tokens, END_SUBSHELL, ind);
	if (!p_sub_args->sub)
		return (1);
	(*ind)++;
	if (get_type(tokens, *ind) == COMMAND)
	{
		dir = get_dir(tokens, *ind);
		while (dir != NOT_DIR)
		{
			if (fill_redir(&p_sub_args->dir_args, tokens, ind, dir))
				return (1);
			(*ind)++;
			if (*ind >= tokens.size)
				return (0);
			dir = get_dir(tokens, *ind);
		}
	}
	return (0);
}

static int	create_operator(t_ast **p_root, t_type type,
				t_vector tokens, size_t *ind)
{
	t_ast	*tmp;

	tmp = create_leaf(type);
	if (!tmp)
		return (1);
	tmp->arguments.op_args.left = *p_root;
	*p_root = tmp;
	(*ind)++;
	(*p_root)->arguments.op_args.right = create_ast(tokens, type + 1, ind);
	if (!(*p_root)->arguments.op_args.right)
		return (1);
	return (0);
}
