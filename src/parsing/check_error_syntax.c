/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:48:59 by jweber            #+#    #+#             */
/*   Updated: 2025/07/04 16:26:53 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "ft_string.h"
#include "parsing.h"

static void	init_smths(char **smth_before, char **smth_after, \
										char **smth_before_after);
static int	perform_checks(t_vector tokens, char **smths[3]);
static int	is_this(char **arr_to_comp, char *str);

#define BEFORE 0
#define AFTER 1
#define BEFORE_AFTER 2

int	check_error_syntax(t_vector tokens)
{
	int		ret;
	char	*smth_before[3];
	char	*smth_after[5];
	char	*smth_before_after[4];
	char	**smths[3];

	init_smths(smth_before, smth_after, smth_before_after);
	smths[BEFORE] = smth_before;
	smths[AFTER] = smth_after;
	smths[BEFORE_AFTER] = smth_before_after;
	ret = perform_checks(tokens, smths);
	return (ret);
}

static void	init_smths(char **smth_before, char **smth_after, \
										char **smth_before_after)
{
	smth_before[0] = ";";
	smth_before[1] = "&";
	smth_before[2] = NULL;
	smth_after[0] = ">";
	smth_after[1] = ">>";
	smth_after[2] = "<";
	smth_after[3] = "<<";
	smth_after[4] = NULL;
	smth_before_after[0] = "|";
	smth_before_after[1] = "||";
	smth_before_after[2] = "&&";
	smth_before_after[3] = NULL;
}

static int	perform_checks(t_vector tokens, char **smths[3])
{
	size_t	i;

	i = 0;
	while (i < tokens.size)
	{
		if (is_this(smths[BEFORE], ((char **)tokens.data)[i]) == 0)
		{
			if (check_before(tokens, i) != 0)
				return (1);
		}
		if (is_this(smths[AFTER], ((char **)tokens.data)[i]) == 0)
		{
			if (check_after_redir(tokens, i) != 0)
				return (1);
		}
		if (is_this(smths[BEFORE_AFTER], ((char **)tokens.data)[i]) == 0)
		{
			if (check_before_after(tokens, i) != 0)
				return (1);
		}
		i++;
	}
	return (0);
}

static int	is_this(char **arr_to_comp, char *str)
{
	size_t	i;

	i = 0;
	while (arr_to_comp[i] != NULL)
	{
		if (ft_strcmp(arr_to_comp[i], str) == 0)
			return (0);
		i++;
	}
	return (1);
}
