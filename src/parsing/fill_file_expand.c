/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_file_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:33:42 by jweber            #+#    #+#             */
/*   Updated: 2025/07/14 16:15:30 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_io.h"
#include "parsing.h"
#include "ft_string.h"
#include <unistd.h>

static int	gnl_here_doc(t_list *env, int fd, char *delimiter, int *p_exiting);
static int	compare_line(char *line, int *p_exiting, char *delimiter);
static int	read_the_line(char **p_line, char *delimiter, int *p_exiting);
static int	transform_write_line(int fd, t_list *env, char *line);

int	fill_file_expand(t_list *env, int fd, char *delimiter)
{
	int		ret;
	int		exiting;

	exiting = 0;
	while (exiting == 0)
	{
		ret = gnl_here_doc(env, fd, delimiter, &exiting);
	}
	return (ret);
}

static int	gnl_here_doc(t_list *env, int fd, char *delimiter, int *p_exiting)
{
	char	*line;
	int		ret;

	ret = read_the_line(&line, delimiter, p_exiting);
	if (*p_exiting == 1)
		return (ret);
	ret = compare_line(line, p_exiting, delimiter);
	if (*p_exiting == 1)
		return (ret);
	ret = transform_write_line(fd, env, line);
	if (ret != 0)
	{
		*p_exiting = 1;
		return (ret);
	}
	return (0);
}

static int	compare_line(char *line, int *p_exiting, char *delimiter)
{
	char	*line_cmp;

	line_cmp = ft_strndup(line, ft_strlen(line) - 1);
	if (line_cmp == NULL)
	{
		free(line);
		*p_exiting = 1;
		return (ERROR_MALLOC);
	}
	if (ft_strcmp(line_cmp, delimiter) == 0)
	{
		*p_exiting = 1;
		free(line);
		free(line_cmp);
		return (0);
	}
	free(line_cmp);
	return (0);
}

static int	read_the_line(char **p_line, char *delimiter, int *p_exiting)
{
	int	err_code;
	int	ret;

	*p_line = get_next_line(0, &err_code);
	if (err_code != 0)
	{
		*p_exiting = 1;
		return (err_code);
	}
	if (*p_line == NULL)
	{
		*p_exiting = 1;
		ret = here_doc_delimited_by_end_of_file(delimiter);
		if (ret != 0)
		{
			return (ERROR_MALLOC);
		}
		return (0);
	}
	return (0);
}

static int	transform_write_line(int fd, t_list *env, char *line)
{
	char	*line_cpy;
	int		ret;

	line_cpy = line;
	ret = here_doc_transform(env, &line_cpy);
	free(line);
	if (ret != 0)
		return (ret);
	if (write(fd, line_cpy, ft_strlen(line_cpy)) < 0)
	{
		free(line_cpy);
		return (ERROR_WRITE);
	}
	free(line_cpy);
	return (0);
}
