/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-19 16:40:04 by cviel             #+#    #+#             */
/*   Updated: 2025-05-19 16:40:04 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ast.h"

char	*print_type(t_type type)
{
	if (type == SUBSHELL)
		return ("SUBSHELL");
	if (type == COMMAND)
		return ("COMMAND");
	if (type == PIPE)
		return ("PIPE");
	if (type == AND)
		return ("AND");
	if (type == OR)
		return ("OR");
	if (type == BACKGROUND)
		return ("BACKGROUND");
	if (type == SEQUENCE)
		return ("SEQUENCE");
	return ("OTHER");
}

char	*print_redir(t_dir dir)
{
	if (dir == IN)
		return ("IN");
	if (dir == OUT)
		return ("OUT");
	if (dir == APPEND)
		return ("APPEND");
	if (dir == HEREDOC)
		return ("HEREDOC");
	return ("NOT_DIR");
}

void	print_tree(t_ast *root, size_t depth)
{
	size_t	i;

	if (root == NULL)
		return ;
	i = 0;
	if (root->type == COMMAND)
	{
		i = 0;
		while (i < depth)
		{
			printf("\t");
			i++;
		}
		printf("COMMAND : args = '");
		i = 0;
		while (i < root->arguments.com_args.content.size - 1)
		{
			printf("%s", ((char **)root->arguments.com_args.content.data)[i]);
			if (i + 1 < root->arguments.com_args.content.size - 1)
				printf(" ");
			i++;
		}
		printf("'");
		i = 0;
		while (i < root->arguments.com_args.dir_args.size)
		{
			printf(" REDIR %lu : %s %s", i + 1, print_redir(((t_dirargs *)root->arguments.com_args.dir_args.data)[i].dir), ((t_dirargs *)root->arguments.com_args.dir_args.data)[i].filename);
			if (i + 1 < root->arguments.com_args.dir_args.size)
				printf(" ");
			i++;
		}
		printf("\n");
	}
	else if (root->type == SUBSHELL)
	{
		i = 0;
		while (i < depth)
		{
			printf("\t");
			i++;
		}
		printf("SUBSHELL");
		i = 0;
		while (i < root->arguments.sub_args.dir_args.size)
		{
			printf(" REDIR %lu : %s %s", i + 1, print_redir(((t_dirargs *)root->arguments.sub_args.dir_args.data)[i].dir), ((t_dirargs *)root->arguments.sub_args.dir_args.data)[i].filename);
			if (i + 1 < root->arguments.sub_args.dir_args.size)
				printf(" ");
			i++;
		}
		printf("\n");
		print_tree(root->arguments.sub_args.sub, depth + 1);
	}
	else
	{
		i = 0;
		while (i < depth)
		{
			printf("\t");
			i++;
		}
		printf("%s\n", print_type(root->type));
		print_tree(root->arguments.op_args.left, depth + 1);
		print_tree(root->arguments.op_args.right, depth + 1);
	}
}
