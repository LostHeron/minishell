/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:39:58 by jweber            #+#    #+#             */
/*   Updated: 2025/08/21 14:35:13 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTING_H
# define PRINTING_H

# include "minishell.h"

void	print_error(int err_code);
void	print_path(t_minishell *p_mini);
void	print_env(t_minishell *p_mini);
void	print_tokens_ast(t_ast *ast);
void	print_tokens(t_vector tokens);
char	*print_type(t_type type);
char	*print_redir_in_out(t_dir dir);
void	print_tree(t_ast *root, size_t depth);
void	print_redir(t_vector redir_vec);
void	print_word(t_vector vec);
int		ft_perror(char *begin, char *file, char *function, char *line);

#endif
