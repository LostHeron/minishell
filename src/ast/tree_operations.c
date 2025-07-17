/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-16 15:03:09 by cviel             #+#    #+#             */
/*   Updated: 2025/06/23 13:25:47 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ast.h"
#include "ft_string.h"
#include "ft_standard.h"
#include <stdio.h>

static t_dir	get_dir(t_vector tokens, size_t ind)
{
	if (((char **)tokens.data)[ind][0] == '<')
	{
		if (!(((char **)tokens.data)[ind][1]))
			return (IN);
		return (HEREDOC);
	}
	if (((char **)tokens.data)[ind][0] == '>')
	{
		if (!(((char **)tokens.data)[ind][1]))
			return (OUT);
		return (APPEND);
	}
	return (NOT_DIR);
}

static t_type	get_type(t_vector tokens, size_t ind)
{
	if (ind >= tokens.size)
		return (END_LINE);
	if (((char **)tokens.data)[ind][0] == '(')
		return (SUBSHELL);
	if (((char **)tokens.data)[ind][0] == ')')
		return (END_SUBSHELL);
	if (((char **)tokens.data)[ind][0] == ';')
		return (SEQUENCE);
	if (((char **)tokens.data)[ind][0] == '|')
	{
		if (!(((char **)tokens.data)[ind][1]))
			return (PIPE);
		return (OR);
	}
	if (((char **)tokens.data)[ind][0] == '&')
	{
		if (!(((char **)tokens.data)[ind][1]))
			return (BACKGROUND);
		return (AND);
	}
	return (COMMAND);
}

static int	fill_redir(t_vector *p_dir_args, t_vector tokens, size_t *ind, t_dir dir)
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

static int	fill_command(t_comargs *p_com_args, t_vector tokens, size_t *ind)
{
	t_dirargs	redir;

	while (get_type(tokens, *ind) == COMMAND)
	{
		redir.dir = get_dir(tokens, *ind);
		if (redir.dir == NOT_DIR)
		{
			redir.filename = ft_strdup(((char **)tokens.data)[*ind]);
			if (!redir.filename)
				return (1);
			if (ft_vector_add_single(&p_com_args->content, &redir.filename))
			{
				free(redir.filename);
				return (1);
			}
		}
		else
		{
			if (fill_redir(&p_com_args->dir_args, tokens, ind, redir.dir))
				return (1);
		}
		(*ind)++;
	}
	redir.filename = NULL;
	if (ft_vector_add_single(&p_com_args->content, &redir.filename))
		return (1);
	return (0);
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
		if (ft_vector_init(&leaf->arguments.com_args.dir_args, 5, sizeof(t_dirargs), free_dirargs))
		{
			free(leaf);
			return (NULL);
		}
		if (ft_vector_init(&leaf->arguments.com_args.content, 5, sizeof(char *), free_command_content))
		{
			ft_vector_free(&leaf->arguments.com_args.dir_args);
			free(leaf);
			return (NULL);
		}
	}
	else if (type == SUBSHELL)
	{
		if (ft_vector_init(&leaf->arguments.sub_args.dir_args, 5, sizeof(t_dirargs), free_dirargs))
		{
			free(leaf);
			return (NULL);
		}
	}
	return (leaf);
}

t_ast	*create_ast(t_vector tokens, t_type max_prio, size_t *ind)
{
	t_ast	*root;
	t_ast	*tmp;
	t_type	type;
	t_dir	dir;

	type = get_type(tokens, *ind);
	if (type >= max_prio)
		return (NULL);
	root = create_leaf(type);
	if (!root)
		return (NULL);
	while (type < max_prio)
	{
		if (type == SUBSHELL)
		{
			(*ind)++;
			root->arguments.sub_args.sub = create_ast(tokens, END_SUBSHELL, ind);
			if (!root->arguments.sub_args.sub)
			{
				free_tree(&root);
				return (NULL);
			}
			(*ind)++;
			if (get_type(tokens, *ind) == COMMAND)
			{
				dir = get_dir(tokens, *ind);
				while (dir != NOT_DIR)
				{
					if (fill_redir(&root->arguments.sub_args.dir_args, tokens, ind, dir))
					{
						free_tree(&root);
						return (NULL);
					}
					(*ind)++;
					if (*ind >= tokens.size)
						dir = NOT_DIR;
					else
						dir = get_dir(tokens, *ind);
				}
			}
		}
		else if (type == COMMAND)
		{	
			if (fill_command(&root->arguments.com_args, tokens, ind))
			{
				free_tree(&root);
				return (NULL);
			}
		}	
		else
		{
			tmp = create_leaf(type);
			if (!tmp)
			{
				free_tree(&root);
				return (NULL);
			}
			tmp->arguments.op_args.left = root;
			root = tmp;
			(*ind)++;
			root->arguments.op_args.right = create_ast(tokens, type + 1, ind);
			if (!root->arguments.op_args.right)
			{
				free_tree(&root);
				return (NULL);
			}
		}
		type = get_type(tokens, *ind);
	}
	return (root);
}
