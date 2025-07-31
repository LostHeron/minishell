/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens_ast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:14:48 by jweber            #+#    #+#             */
/*   Updated: 2025/07/31 11:40:13 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ft_io.h"

static void	print_cmd(t_ast *ast);

void	print_tokens_ast(t_ast *ast)
{
	t_ast	*tmp;

	if (ast != NULL)
	{
		tmp = ast;
		while (tmp->type == PIPE)
		{
			print_cmd(tmp->arguments.op_args.left);
			tmp = tmp->arguments.op_args.right;
		}
		if (ast->type == COMMAND)
		{
			print_cmd(ast);
		}
	}
	else
		ft_printf_fd(2, "ast is not built\n");
}

static void	print_cmd(t_ast *ast)
{
	size_t	i;

	i = 0;
	ft_printf_fd(2, "arguments : ");
	while (i < ast->arguments.com_args.content.size)
	{
		ft_printf_fd(2,
			" '%s',", ((char **)ast->arguments.com_args.content.data)[i]);
		i++;
	}
	ft_printf_fd(2, "\n\n");
}
