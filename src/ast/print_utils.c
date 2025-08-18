/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:09:45 by cviel             #+#    #+#             */
/*   Updated: 2025/08/18 13:43:10 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (type == SEQUENCE)
		return ("SEQUENCE");
	return ("END NODE");
}

char	*print_redir_in_out(t_dir dir)
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
