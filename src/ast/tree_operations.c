/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:03:09 by cviel             #+#    #+#             */
/*   Updated: 2025/08/06 15:38:27 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ast.h"
#include "ft_string.h"
#include "ft_standard.h"

int			fill_redir(t_vector *p_dir_args, t_vector tokens,
				size_t *ind, t_dir dir);
static int	fill_content(t_vector *p_content, t_vector tokens, size_t ind);

int	fill_command(t_comargs *p_com_args, t_vector tokens, size_t *ind)
{
	t_dir	dir;
	char	*null_string;

	while (get_type(tokens, *ind) == COMMAND)
	{
		dir = get_dir(tokens, *ind);
		if (dir == NOT_DIR)
		{
			if (fill_content(&p_com_args->content, tokens, *ind))
				return (1);
		}
		else
		{
			if (fill_redir(&p_com_args->dir_args, tokens, ind, dir))
				return (1);
		}
		(*ind)++;
	}
	null_string = NULL;
	if (ft_vector_add_single(&p_com_args->content, &null_string))
		return (1);
	return (0);
}

int	create_subshell(t_subargs *p_sub_args, t_vector tokens, size_t *ind)
{
	t_dir	dir;

	(*ind)++;
	p_sub_args->sub = create_ast(tokens, SUBSHELL_PRIO, ind);
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

int	create_operator(t_ast **p_root, t_type type, t_vector tokens, size_t *ind)
{
	t_ast	*tmp;

	tmp = create_leaf(type);
	if (!tmp)
		return (1);
	tmp->arguments.op_args.left = *p_root;
	*p_root = tmp;
	(*ind)++;
	(*p_root)->arguments.op_args.right
		= create_ast(tokens, get_prio(type), ind);
	if (!(*p_root)->arguments.op_args.right)
		return (1);
	return (0);
}

int	fill_redir(t_vector *p_dir_args, t_vector tokens, size_t *ind, t_dir dir)
{
	t_dirargs	redir;

	redir.dir = dir;
	(*ind)++;
	if (get_type(tokens, *ind) != COMMAND || get_dir(tokens, *ind) != NOT_DIR)
		return (1);
	redir.filename = ft_strdup(((char **)tokens.data)[*ind]);
	if (!redir.filename)
		return (1);
	if (ft_vector_add_single(p_dir_args, &redir))
	{
		free(redir.filename);
		return (1);
	}
	return (0);
}

static int	fill_content(t_vector *p_content, t_vector tokens, size_t ind)
{
	char	*content;

	content = ft_strdup(((char **)tokens.data)[ind]);
	if (!content)
		return (1);
	if (ft_vector_add_single(p_content, &content))
	{
		free(content);
		return (1);
	}
	return (0);
}
