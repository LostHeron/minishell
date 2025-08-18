/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:10:14 by cviel             #+#    #+#             */
/*   Updated: 2025/08/18 13:11:31 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ast.h"
#include "ft_vectors.h"

t_ast	*create_leaf(t_type type);

/* to check
 *	-> create_leaf : DONE -> OK !
 *	-> create_subshell : DONE -> OK !
 *	-> fill_command : DONE -> OK !
 *	-> create_operator : DONE -> OK !
*/
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

/* to check
 *	-> first ft_vector_init -> OK !
 *	-> second ft_vector_init -> OK !
*/
static int	init_vectors(t_vector *dir_args, t_vector *content)
{
	int	ret;

	ret = ft_vector_init(dir_args, 5, sizeof(t_dirargs), free_dirargs);
	if (ret != 0)
		return (ret);
	ret = ft_vector_init(content, 5, sizeof(char *), free_command_content);
	if (ret != 0)
	{
		ft_vector_free(dir_args);
	}
	return (ret);
}

/* to check
 *	-> first malloc fail : DONE -> OK !
 *	-> init_vector fail : DONE -> OK !
 *	-> ft_vector_init : DONE -> OK !
*/
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
			free(leaf);
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
