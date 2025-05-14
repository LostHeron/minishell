/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:04:27 by jweber            #+#    #+#             */
/*   Updated: 2025/05/14 18:12:12 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

int		parse_line(char *line, t_ast **p_ast);
void	print_ast(t_ast *ast);
char	**ft_split_args(char *line, char **args, int *p_err_code);
int		ft_countwords_args(char *line, char **args, int *p_err_code);
char	*ft_strstr_args(char *line, char **args);
int		handle_single_quotes(char *line, int *p_i, \
						int *p_word_i, int *p_err_code);
int		handle_double_quotes(char *line, int *p_i, \
						int *p_word_i, int *p_err_code);
int		handle_parenthesis(char *line, int *p_i, \
						int *p_word_i, int *p_err_code);

#endif
