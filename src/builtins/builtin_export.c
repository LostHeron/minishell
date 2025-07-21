/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:34:56 by jweber            #+#    #+#             */
/*   Updated: 2025/07/16 17:12:24 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "minishell.h"
#include <stdio.h>

int			builtin_export_with_args(t_vector args, t_minishell *p_mini);
int			builtin_export_no_args(t_minishell *p_mini);

/* 
 * function called when export is used in command line 
 * return :
 *	in case of success : return 0
 *	in case of failure :
 *		if it is an error which we should stop the shell
 *			-> negative integer
 *		if it is an error which (like bad env name)
 *			-> positive integer
*/
int	builtin_export(t_vector args, t_minishell *p_mini)
{
	size_t	ret;

	ret = 0;
	if (args.size == 2)
	{
		ret = builtin_export_no_args(p_mini);
	}
	else
	{
		ret = builtin_export_with_args(args, p_mini);
	}
	return (ret);
}
