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
	return ("SEQUENCE");
}

char	*print_redir(t_dir dir)
{
	if (dir == IN)
		return ("IN");
	if (dir == OUT)
		return ("OUT");
	return ("APPEND");
}

void	print_tree(t_ast *root, int depth)
{
	t_dirargs	*list_i;
	int			i;

	if (root == NULL)
		return ;
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
		while (root->arguments.com_args->content[i])
		{
			printf("%s", root->arguments.com_args->content[i]);
			if (root->arguments.com_args->content[i + 1])
				printf(" ");
			i++;
		}
		printf("'");
		if (root->arguments.com_args->dir_args)
		{
			list_i = root->arguments.com_args->dir_args;
			i = 0;
			while (list_i)
			{
				printf(" REDIR %d : %s %s", i + 1, print_redir(list_i->dir), list_i->filename);
				if (list_i->next)
					printf(" ");
				list_i = list_i->next;
				i++;
			}
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
		printf("SUBSHELL\n");
		print_tree(root->arguments.sub_args, depth + 1);
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
