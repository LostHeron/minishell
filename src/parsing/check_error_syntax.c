/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:48:59 by jweber            #+#    #+#             */
/*   Updated: 2025/06/25 17:03:07 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"

int	check_error_syntax(t_vector tokens)
{
	size_t	i;
	int		ret;
	char	*smth_before[3];
	char	*smth_after[5];
	char	*smth_before_after[4];

	i = 0;
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
	while (i < tokens.size)
	{
		if (check_before(smth_before, tokens) != 0)
		{
			return (1);
		}
		if (check_after(smth_after, tokens) != 0)
		{
			return (1);
		}
		if (check_before_after(smth_before_after, tokens) != 0)
		{
			return (1);
		}
		/*
		check_for(";"); // cmd before !
		check_for("&");	// cmd before !
		check_for("||"); // cmd before and after !
		check_for("|");	// cmd before and after !
		check_for("&&"); // cmd before and after !
		check_for(">"); // must have somehting after 
		check_for("<"); // must have something after 
		check_for("<<"); // must have somehting after
		check_for(">>"); // must have somehting after
		*/
		i++;
	}
}

static int	check_before(char **to_check, t_vector tokens)
{
	size_t	i;
}

static int	check_after(char **to_check, t_vector tokens)
{
}

static int	check_before_after(char **to_check, t_vector tokens)
{
}
