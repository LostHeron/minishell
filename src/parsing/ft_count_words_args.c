/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:43:29 by jweber            #+#    #+#             */
/*   Updated: 2025/05/14 18:14:59 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "parsing.h"
#include "minishell.h"

int	ft_countwords_args(char *line, char **args, int *p_err_code)
{
	int	nb_words;
	int	i;

	(void) args;
	nb_words = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] && ft_strchr(WHITE_SPACES, line[i]))
			i++;
		if (handle_single_quotes(line, &i, &nb_words, p_err_code) != 0)
			return (*p_err_code);
		if (handle_double_quotes(line, &i, &nb_words, p_err_code) != 0)
			return (*p_err_code);
		if (handle_parenthesis(line, &i, &nb_words, p_err_code) != 0)
			return (*p_err_code);
		ft_strstr_args(line, args);
		i++;
	}
	return (nb_words);
}
