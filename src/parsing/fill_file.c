/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:36:16 by jweber            #+#    #+#             */
/*   Updated: 2025/08/14 16:33:49 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "ft_string.h"
#include <readline/readline.h>
#include <unistd.h>
#include <stdio.h>

static int	case_expanding(t_minishell *p_mini, char **p_line,
				char **p_line_cpy);
static int	write_line(int fd, char *line);

/* to check
 *	-> rl_here_doc fail : TO DO ;
 *	-> case_expanding fail : TO DO ;
 *	-> write_line fail : TO DO ;
*/
int	fill_file(t_minishell *p_mini, int fd, char *delimiter, int expand)
{
	int		ret;
	int		exiting;
	char	*line;
	char	*line_cpy;

	exiting = 0;
	while (exiting == 0)
	{
		ret = rl_here_doc(p_mini, &line, delimiter, &exiting);
		if (exiting == 1)
			return (ret);
		if (expand == 1)
		{
			ret = case_expanding(p_mini, &line, &line_cpy);
			if (ret < 0)
				return (ret);
		}
		ret = write_line(fd, line);
		free(line);
		if (ret != 0)
			return (ret);
	}
	return (ret);
}

static int	case_expanding(t_minishell *p_mini, char **p_line,
			char **p_line_cpy)
{
	int	ret;

	*p_line_cpy = *p_line;
	ret = here_doc_transform(p_mini->env, p_line_cpy);
	free(*p_line);
	*p_line = *p_line_cpy;
	return (ret);
}

static int	write_line(int fd, char *line)
{
	ssize_t	nb_write;

	nb_write = write(fd, line, ft_strlen(line));
	if (nb_write < 0)
	{
		perror("write");
		return (ERROR_WRITE);
	}
	return (0);
}
