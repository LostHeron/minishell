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

int			tokenize(t_minishell *p_mini, t_vector *p_tokens, int *p_err_code);
int			prepare_here_doc(t_minishell *p_mini, t_vector *p_tokens);
int			check_parenthesis(char *line);
int			check_error_syntax(t_vector tokens);
int			count_here_doc(t_vector tokens);
int			get_here_doc(t_minishell *p_mini, t_vector *p_tokens);
int			lexer(char *line, t_vector *p_tokens);
t_vector	ft_split_args(char *line, char **args, int *p_err_code);
char		*get_next_token(char **p_line, char **args, int *p_err_code);
char		**init_args(int *p_err_code);
size_t		ft_strstr_args(char *line, char **args);

#endif
