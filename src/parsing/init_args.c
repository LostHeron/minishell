/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:30:34 by jweber            #+#    #+#             */
/*   Updated: 2025/05/16 10:31:34 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_standard.h"

char	**init_args(int *p_err_code)
{
	char	**args;

	args = ft_malloc(9 * sizeof(char *));
	args[8] = NULL;
	if (args == NULL)
	{
		*p_err_code = ERROR_MALLOC;
		return (NULL);
	}
	args[0] = "&&";
	args[1] = "||";
	args[2] = "<<";
	args[3] = ">>";
	args[4] = "|";
	args[5] = "&";
	args[6] = ">";
	args[7] = "<";
	return (args);
}
