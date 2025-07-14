/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:30:34 by jweber            #+#    #+#             */
/*   Updated: 2025/06/16 12:50:43 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_standard.h"

int	init_args(char ***p_args)
{
	*p_args = ft_malloc(11 * sizeof(char *));
	if (*p_args == NULL)
	{
		return (ERROR_MALLOC);
	}
	(*p_args)[10] = NULL;
	(*p_args)[0] = "&&";
	(*p_args)[1] = "||";
	(*p_args)[2] = "<<";
	(*p_args)[3] = ">>";
	(*p_args)[4] = "|";
	(*p_args)[5] = "&";
	(*p_args)[6] = ">";
	(*p_args)[7] = "<";
	(*p_args)[8] = "(";
	(*p_args)[9] = ")";
	return (0);
}
