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
# include "ft_vectors.h"

int			parse_line(char *line, t_ast **p_ast);
void		print_ast(t_ast *ast);
t_vector	ft_split_args(char *line, char **args, int *p_err_code);
char		*get_next_token(char **p_line, char **args, int *p_err_code);
char		**init_args(int *p_err_code);
size_t		ft_strstr_args(char *line, char **args);

#endif
