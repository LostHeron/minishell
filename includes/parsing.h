/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:04:27 by jweber            #+#    #+#             */
/*   Updated: 2025/07/02 16:33:30 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "ft_vectors.h"
# include "minishell.h"

int			tokenize(t_minishell *p_mini, t_vector *p_tokens);
int			prepare_here_doc(t_minishell *p_mini, t_vector *p_tokens);
int			check_parenthesis(char *line);
int			check_error_syntax(t_vector tokens);
int			count_here_doc(t_vector tokens);
int			get_here_doc(t_minishell *p_mini, t_vector *p_tokens);
int			lexer(char *line, t_vector *p_tokens);
int			ft_split_args(t_vector *p_tokens, char *line, char **args);
int			get_next_token(char **p_token_i, char **p_line, char **args);
int			init_args(char ***p_args);
size_t		ft_strstr_args(char *line, char **args);

#endif
