/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:28:36 by jweber            #+#    #+#             */
/*   Updated: 2025/05/14 17:57:40 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

size_t	ft_strstr_args(char *line, char **args)
{
	int		arg_i;
	size_t	arg_len;

	arg_i = 0;
	while (args[arg_i] != NULL)
	{
		arg_len = ft_strlen(args[arg_i]);
		if (ft_strncmp(line, args[arg_i], arg_len) == 0)
			return (arg_len);
		arg_i++;
	}
	return (0);
}
