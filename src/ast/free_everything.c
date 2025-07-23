/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 17:42:41 by cviel             #+#    #+#             */
/*   Updated: 2025-05-23 17:42:41 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ast.h"
#include "ft_vectors.h"

void	free_dirargs(t_vector *dirargs_ptr)
{
	size_t	i;

	i = 0;
	while (i < dirargs_ptr->size)
	{
		free(((t_dirargs *)dirargs_ptr->data)[i].filename);
		i++;
	}
	free(dirargs_ptr->data);
}

void	free_command_content(t_vector *content_ptr)
{
	size_t	i;

	i = 0;
	while (i < content_ptr->size)
	{
		free(((char **)content_ptr->data)[i]);
		i++;
	}
	free(content_ptr->data);
}

void	free_tree(t_ast **root)
{
	if (!(*root))
		return ;
	if ((*root)->type == COMMAND)
	{
		ft_vector_free(&(*root)->arguments.com_args.dir_args);
		ft_vector_free(&(*root)->arguments.com_args.content);
	}
	else if ((*root)->type == SUBSHELL)
	{
		ft_vector_free(&(*root)->arguments.sub_args.dir_args);
		free_tree(&(*root)->arguments.sub_args.sub);
	}
	else if ((*root)->type != END_LINE)
	{
		free_tree(&(*root)->arguments.op_args.left);
		free_tree(&(*root)->arguments.op_args.right);
	}
	free(*root);
}
