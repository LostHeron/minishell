/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_file_no_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:44:08 by jweber            #+#    #+#             */
/*   Updated: 2025/07/14 16:16:27 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_io.h"
#include "parsing.h"
#include "ft_string.h"
#include <complex.h>
#include <unistd.h>
#include <stdio.h>

static int	gnl_here_doc(int fd, char *delimiter, int *p_exiting);
static int	compare_line(char *line, int *p_exiting, char *delimiter);
static int	read_the_line(char **p_line, char *delimiter, int *p_exiting);
static int	write_line(int fd, char *line);

/* to check
 *	-> gnl_here_doc fail : DONE -> OK !
*/
int	fill_file_no_expand(int fd, char *delimiter)
{
	int		ret;
	int		exiting;

	exiting = 0;
	while (exiting == 0)
	{
		ret = gnl_here_doc(fd, delimiter, &exiting);
	}
	return (ret);
}

/* to check :
 *	-> read_the_line fail : DONE -> OK !
 *	-> compare_line : DONE -> OK !
 *	-> write_line : DONE -> OK !
*/
static int	gnl_here_doc(int fd, char *delimiter, int *p_exiting)
{
	char	*line;
	int		ret;

	ret = read_the_line(&line, delimiter, p_exiting);
	if (*p_exiting == 1)
		return (ret);
	ret = compare_line(line, p_exiting, delimiter);
	if (*p_exiting == 1)
		return (ret);
	ret = write_line(fd, line);
	if (ret != 0)
	{
		*p_exiting = 1;
		return (ret);
	}
	return (0);
}

/* to check
 *	-> ft_strndup fail : DONE -> OK !
*/
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

/* to check
 *	-> gnl fail : DONE -> OK !
 *	-> here_doc_delimited_by_end_of_file fail : DONE -> OK !
*/
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

/* to check : 
 *	-> write fail : DONE -> OK !
*/
static int	write_line(int fd, char *line)
{
	int	nb_write;

	nb_write = write(fd, line, ft_strlen(line));
	if (nb_write < 0)
	{
		perror("write");
		free(line);
		return (ERROR_WRITE);
	}
	free(line);
	return (0);
}
