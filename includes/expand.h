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
int	expand_redir(t_vector *p_redir, t_minishell mini);
int	split_elem(t_vector *splitted, char *src);
int	expand_variables(t_vector splitted, t_minishell mini);
int	remove_last(t_exp *p_exp_part, int p_ind);
int	replace_key_value(t_exp *p_exp_part, int *p_ind, int len_key, t_env *p_env);
int	replace_err_code(t_exp *p_exp_part, int *p_ind, t_minishell mini);
int	rebuild_elem(t_vector *dest, t_vector splitted);
int	rebuild_filename(t_vector *dest, int ind, t_vector splitted);

#endif
