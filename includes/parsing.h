/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:04:27 by jweber            #+#    #+#             */
/*   Updated: 2025/05/16 14:22:43 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "ft_vectors.h"

int			lexer(char *line, t_vector *p_tokens);
t_vector	ft_split_args(char *line, char **args, int *p_err_code);
char		*get_next_token(char **p_line, char **args, int *p_err_code);
char		**init_args(int *p_err_code);
size_t		ft_strstr_args(char *line, char **args);

#endif
