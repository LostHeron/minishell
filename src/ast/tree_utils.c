/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:14:33 by cviel             #+#    #+#             */
/*   Updated: 2025/08/08 15:16:05 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ast.h"
#include "ft_vectors.h"
#include "ft_string.h"

t_type	get_type(t_vector tokens, size_t ind)
{
	if (ind >= tokens.size)
		return (END_LINE);
	if (ft_strcmp(((char **)tokens.data)[ind], "(") == 0)
		return (SUBSHELL);
	if (ft_strcmp(((char **)tokens.data)[ind], ")") == 0)
		return (END_SUBSHELL);
	if (ft_strcmp(((char **)tokens.data)[ind], ";") == 0)
		return (SEQUENCE);
	if (ft_strcmp(((char **)tokens.data)[ind], "|") == 0)
		return (PIPE);
	if (ft_strcmp(((char **)tokens.data)[ind], "||") == 0)
		return (OR);
	if (ft_strcmp(((char **)tokens.data)[ind], "&&") == 0)
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

t_prio	get_prio(t_type type)
{
	if (type == COMMAND || type == SUBSHELL)
		return (COMMAND_PRIO);
	if (type == PIPE)
		return (PIPE_PRIO);
	if (type == AND || type == OR)
		return (LOGICAL_PRIO);
	if (type == SEQUENCE)
		return (SEQUENCE_PRIO);
	if (type == END_SUBSHELL)
		return (SUBSHELL_PRIO);
	return (END_LINE_PRIO);
}
