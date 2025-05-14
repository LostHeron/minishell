/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:23:59 by jweber            #+#    #+#             */
/*   Updated: 2025/05/14 16:45:23 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>

/* this is the first split, which should separat all key word one by one !
 * this is achived by providing a list of the 'reserved key word as args'
 * like : args[0] = "&&", args[1] = "if", args[4] = "|", ..., args[n] = ">"
 * and this list is used on each place on the line to separate each token 
 * independantly !
 *
 * NOTE ! : args order is important and all args should be placed in order of 
 * precedance !
*/
char	**ft_split_args(char *line, char **args, int *p_err_code)
{
	int	i;
	int	j;
	int	arg_i;
	int	nb_words;

	(void)i;
	(void)j;
	(void)arg_i;
	nb_words = ft_countwords_args(line, args, p_err_code);
	if (*p_err_code != 0)
		return (NULL);
	return (NULL);
	/*
	while (line[i])
	{
		ft_strstr_args(line, args);
	}
	*/
}
