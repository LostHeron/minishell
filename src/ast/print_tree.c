/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:40:04 by cviel             #+#    #+#             */
/*   Updated: 2025/08/05 18:30:52 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ast.h"
#include "ft_io.h"

static void	print_tabs(size_t depth);
static void	print_content(t_vector content);
static void	print_all_redir(t_vector dir_args);

void	print_tree(t_ast *root, size_t depth)
{
	if (root == NULL)
		return ;
	print_tabs(depth);
	ft_printf_fd(2, "%s", print_type(root->type));
	if (root->type == COMMAND)
	{
		print_content(root->arguments.com_args.content);
		print_all_redir(root->arguments.com_args.dir_args);
	}
	else if (root->type == SUBSHELL)
	{
		print_all_redir(root->arguments.sub_args.dir_args);
		print_tree(root->arguments.sub_args.sub, depth + 1);
	}
	else
	{
		ft_printf_fd(2, "\n");
		print_tree(root->arguments.op_args.left, depth + 1);
		print_tree(root->arguments.op_args.right, depth + 1);
	}
}

static void	print_tabs(size_t depth)
{
	size_t	i;

	i = 0;
	while (i < depth)
	{
		ft_printf_fd(2, "\t");
		i++;
	}
}

static void	print_content(t_vector content)
{
	size_t	i;

	ft_printf_fd(2, " : args = '");
	i = 0;
	while (i < content.size - 1)
	{
		ft_printf_fd(2, "%s", ((char **)content.data)[i]);
		if (i + 1 < content.size - 1)
			ft_printf_fd(2, " ");
		i++;
	}
	ft_printf_fd(2, "'");
}

static void	print_all_redir(t_vector dir_args)
{
	size_t	i;

	i = 0;
	while (i < dir_args.size)
	{
		ft_printf_fd(2, " REDIR %lu : %s %s", i + 1,
			print_redir_in_out(((t_dirargs *)dir_args.data)[i].dir),
			((t_dirargs *)dir_args.data)[i].filename);
		if (i + 1 < dir_args.size)
			ft_printf_fd(2, " ");
		i++;
	}
	ft_printf_fd(2, "\n");
}
