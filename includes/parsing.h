/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:04:27 by jweber            #+#    #+#             */
/*   Updated: 2025/08/06 14:54:37 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "ft_vectors.h"
# include "minishell.h"

int		tokenize(t_minishell *p_mini, t_vector *p_tokens);
int		line_to_tokens(t_minishell *p_mini, t_vector *p_tokens);
int		prepare_here_docs(t_minishell *p_mini, t_vector *p_tokens);
int		get_here_doc(t_minishell *p_mini, t_vector *p_tokens);
int		write_to_here_doc(t_minishell *p_mini, t_vector *p_tokens, int i,
			int *p_hd_count);
int		generate_hd_filename(char **p_filename, size_t	nb);
char	*get_real_delimiter(char *delimiter);
int		here_doc_delimited_by_end_of_file(char *delimiter);
int		fill_file(t_minishell *p_mini, int fd, char *delimiter, int expand);
int		here_doc_transform(t_list *env, char **p_line);
char	*get_value(t_list *env, char *key);
char	*get_key(char *line);
int		ft_split_args(t_vector *p_tokens, char *line, char **args);
int		get_next_token(char **p_token_i, char **p_line, char **args);
size_t	ft_strstr_args(char *line, char **args);

#endif
