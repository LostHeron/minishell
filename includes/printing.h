/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:39:58 by jweber            #+#    #+#             */
/*   Updated: 2025/08/08 15:01:36 by jweber           ###   ########.fr       */
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
void	print_redir(t_vector redir_vec);
int		ft_perror(char *begin, char *file, char *function, char *line);

#endif
