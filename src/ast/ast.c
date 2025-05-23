/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-16 14:08:51 by cviel             #+#    #+#             */
/*   Updated: 2025-05-16 14:08:51 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	get_ast(char **tokens)
{
	t_ast	*root;
	int		i;

	i = 0;
	root = create_tree(tokens, END_SUBSHELL + 1, &i);
	if (!root)
		return (1);
	print_tree(root, 0);
	free_tree(&root);
	return (0);
}
