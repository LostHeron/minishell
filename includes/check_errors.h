/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:53:26 by jweber            #+#    #+#             */
/*   Updated: 2025/08/06 14:58:39 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_ERRORS_H
# define CHECK_ERRORS_H

# include "minishell.h"
# include "ft_vectors.h"

int	check_errors(t_minishell *p_mini, t_vector *p_tokens);
int	check_matching_parenthesis(t_vector *p_tokens);
int	check_error_syntax(t_vector tokens);
int	check_around_parenthesis(t_vector *p_tokens);
int	check_around_opening_parenthesis(t_vector *p_tokens, size_t	token_i);
int	check_after_closing_parenthesis(t_vector *p_tokens, size_t token_i);
int	check_around_closing_parenthesis(t_vector *p_tokens, size_t	token_i);
int	check_before_after(t_vector tokens, size_t i);
int	check_before(t_vector tokens, size_t i);
int	check_after_redir(t_vector tokens, size_t i);
int	check_after(t_vector tokens, size_t i);
int	count_here_doc(t_vector tokens);

#endif
