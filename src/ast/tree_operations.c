/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-16 15:03:09 by cviel             #+#    #+#             */
/*   Updated: 2025-05-16 15:03:09 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ast.h"
#include <stdio.h>

static t_type	get_type(char *s)
{
	int	i;

	if (!s)
		return (END_SUBSHELL + 1);
	i = 0;
	if (s[i] == '(')
		return (SUBSHELL);
	if (s[i] == ')')
		return (END_SUBSHELL);
	if (s[i] == ';')
		return (SEQUENCE);
	if (s[i] == '|')
	{
		if (!s[i + 1])
			return (PIPE);
		return (OR);
	}
	if (s[i] == '&')
	{
		if (!s[i + 1])
			return (BACKGROUND);
		return (AND);
	}
	return (COMMAND);
}

void	free_list(t_dirargs **dir_args)
{
	if (!(*dir_args))
		return ;
	if ((*dir_args)->next)
		free_list(&(*dir_args)->next);
	free((*dir_args));
	*dir_args = NULL;
}

t_dirargs	*create_node(char *content, t_dir dir)
{
	t_dirargs	*redir;

	redir = malloc(sizeof(t_dirargs));
	if (!redir)
		return (NULL);
	redir->dir = dir;
	redir->filename = content;
	redir->next = NULL;
	return (redir);
}

void	list_append(t_dirargs **list_args, t_dirargs *arg)
{
	t_dirargs	*list_i;

	if (!(*list_args))
	{
		*list_args = arg;
		return ;
	}
	list_i = *list_args;
	while (list_i->next)
		list_i = list_i->next;
	list_i->next = arg;
}

int	fill_command(t_ast *root, char **av, int *ind)
{
	t_dirargs	*redir;
	t_type		type;
	int			i;

	type = get_type(av[*ind]);
	i = 0;
	while (av[*ind + i] && type == COMMAND)
	{
		if (av[*ind + i][0] == '<' || av[*ind + i][0] == '>')
			i++;
		i++;
	}
	root->arguments.com_args->content = malloc(sizeof(char *) * (i + 1));
	if (!root->arguments.com_args->content)
		return (1);
	type = get_type(av[*ind]);
	i = 0;
	while (av[*ind] && type == COMMAND)
	{
		if (av[*ind][0] == '<')
		{
			redir = create_node(av[*ind + 1], IN);
			if (!redir)
				return (1);
			list_append(&root->arguments.com_args->dir_args, redir);
			(*ind)++;
		}
		else if (av[*ind][0] == '>')
		{
			if (av[*ind][1])
				redir = create_node(av[*ind + 1], APPEND);
			else
				redir = create_node(av[*ind + 1], OUT);
			if (!redir)
				return (1);
			list_append(&root->arguments.com_args->dir_args, redir);
			(*ind)++;
		}
		else
		{
			root->arguments.com_args->content[i] = av[*ind];
			i++;
		}
		(*ind)++;
		type = get_type(av[*ind]);
	}
	root->arguments.com_args->content[i] = NULL;
	return (0);
}

void	free_tree(t_ast **root)
{
	if (!(*root))
		return ;
	if ((*root)->type == COMMAND)
	{
		free_list(&(*root)->arguments.com_args->dir_args);
		free((*root)->arguments.com_args->content);
		free((*root)->arguments.com_args);
	}
	else if ((*root)->type == SUBSHELL)
		free_tree(&(*root)->arguments.sub_args);
	else
	{
		free_tree(&(*root)->arguments.op_args.left);
		free_tree(&(*root)->arguments.op_args.right);
	}
	free(*root);
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
		leaf->arguments.com_args = malloc(sizeof(t_comargs));
		if (!leaf->arguments.com_args)
		{
			free(leaf);
			return (NULL);
		}
		leaf->arguments.com_args->dir_args = NULL;
	}
	return (leaf);
}

t_ast	*create_tree(char **av, t_type max_prio, int *ind)
{
	t_ast	*root;
	t_ast	*tmp;
	t_type	type;

	type = get_type(av[*ind]);
	root = create_leaf(type);
	if (!root)
		return (NULL);
	while (av[*ind] && type < max_prio)
	{
		if (type == SUBSHELL)
		{
			(*ind)++;
			root->arguments.sub_args = create_tree(&av[0], END_SUBSHELL, ind);
			if (!root->arguments.sub_args)
			{
				free_tree(&root);
				return (NULL);
			}
		}
		else if (type == END_SUBSHELL)
			(*ind)++;
		else if (type == COMMAND)
		{	
			if (fill_command(root, &av[0], ind))
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
			root->arguments.op_args.right = create_tree(&av[0], type, ind);
			if (!root->arguments.op_args.right)
			{
				free_tree(&root);
				return (NULL);
			}
		}
		type = get_type(av[*ind]);
	}
	return (root);
}
