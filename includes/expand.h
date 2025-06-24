/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-20 13:30:21 by cviel             #+#    #+#             */
/*   Updated: 2025-06-20 13:30:21 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"
# include "ft_vectors.h"

enum e_quote
{
	NONE = 0,
	SINGLE,
	DOUBLE
};

typedef struct s_exp
{
	enum e_quote	quote;
	char			*content;
}	t_exp;

int	expand(t_vector *p_args, t_minishell mini);
int	split_elem(t_vector *splitted, char *src);
int	expand_variables(t_vector splitted, t_minishell mini);
int	rebuild_elem(t_vector *dest, t_vector splitted);

#endif
