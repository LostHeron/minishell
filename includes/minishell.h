/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:39:55 by jweber            #+#    #+#             */
/*   Updated: 2025/05/13 18:02:07 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_ast
{
	char	*value;
	void	*left;
	void	*right;
}	t_ast;

int		parsing(char *line, t_ast *ast);
void	print_ast(t_ast ast);

#endif
