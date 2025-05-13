/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:37:10 by jweber            #+#    #+#             */
/*   Updated: 2025/05/07 13:41:49 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	char	*line;
	int		err_code;

	//t_tree	my_tree;
	err_code = 0;
	while (err_code == 0)
	{
		line = readline("prompt >> ");
		printf("line = %s\n", line);
		//my_tree = parse_line(line);
		//if my_tree != NULL
		//	exec_line(my_tree);
		free(line);
	}
	return (0);
}
