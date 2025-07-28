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

int			fill_redir(t_vector *p_dir_args, t_vector tokens,
				size_t *ind, t_dir dir);
static int	fill_content(t_vector *p_content, t_vector tokens, size_t ind);

t_type	get_type(t_vector tokens, size_t ind)
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
	if (((char **)tokens.data)[ind][0] == '&'
		&& ((char **)tokens.data)[ind][0] == '&')
		return (AND);
	return (COMMAND);
}

t_dir	get_dir(t_vector tokens, size_t ind)
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
