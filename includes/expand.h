/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:30:21 by cviel             #+#    #+#             */
/*   Updated: 2025/07/31 18:01:10 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

#include <unistd.h>
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

typedef struct s_pat
{
	char	c;
	int		wild;
}	t_pat;

int		expand(t_vector *p_args, t_minishell mini);
int		expand_all(t_vector *p_splitted, t_minishell mini);
int		expand_redir(t_vector *p_redir, t_minishell mini);
int		split_elem(t_vector *splitted, char *src);
int		expand_variables(t_vector splitted, t_minishell mini);
int		word_split(t_vector *p_splitted);
int		expand_wildcard(t_vector *p_splitted);
int		replace_key_value(t_exp *p_exp_part,
			int *p_ind, int len_key, t_env *p_env);
int		replace_err_code(t_exp *p_exp_part, int *p_ind, t_minishell mini);
int		rebuild_elem(t_vector *dest, t_vector splitted);
int		rebuild_filename(t_vector *dest, int ind, t_vector splitted);
int		rebuild_exp(t_vector *dest, t_vector splitted, size_t ind);
int		find_match(t_vector *p_names, t_vector pattern);
int		matching(t_vector pattern, char *elem, int *p_match);
int		handle_wildcard(t_vector *p_splitted, size_t *p_vec_ind, t_vector names);
int		remove_last(t_exp *p_exp_part, int p_ind);
void	free_exp(t_vector *word);
void	free_data(t_vector *p_vector);
void	free_tab(char **arr);
void 	free_splitted(t_vector *p_word);

#endif
