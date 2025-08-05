/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:36:16 by jweber            #+#    #+#             */
/*   Updated: 2025/08/05 14:06:32 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "ft_string.h"
#include "ft_input.h"
#include "ft_io.h"
#include <readline/readline.h>
#include <unistd.h>
#include <stdio.h>

static int	rl_here_doc(char **p_line, char *delimiter, int *p_exiting);
static int	compare_line(char *line, int *p_exiting, char *delimiter);
static int	read_the_line(char **p_line, char *delimiter, int *p_exiting);
//static int	transform_write_line(int fd, t_list *env, char *line);
static int	write_line(int fd, char *line);
static char	*get_prompt_hd(char *delimiter);

/* to check
 *	-> gnl_here_doc fail : DONE -> OK!
*/
int	fill_file(t_list *env, int fd, char *delimiter, int expand)
{
	int		ret;
	int		exiting;
	char	*line;
	char	*line_cpy;

	exiting = 0;
	while (exiting == 0)
	{
		ret = rl_here_doc(&line, delimiter, &exiting);
		if (exiting == 1)
			return (ret);
		if (expand == 1)
		{
			line_cpy = line;
			ret = here_doc_transform(env, &line_cpy);
			free(line);
			if (ret != 0)
			{
				exiting = 1;
				return (ret);
			}
			line = line_cpy;
		}
		ret = write_line(fd, line);
		if (ret != 0)
		{
			exiting = 1;
			return (ret);
		}
	}
	return (ret);
}

/* to check :
 *	-> read_the_line fail : DONE -> OK !
 *	-> compare_line fail : DONE -> OK !
 *	-> transform_write_line fail : DONE -> OK !
*/
static int	rl_here_doc(char **p_line, char *delimiter, int *p_exiting)
{
	int		ret;

	ret = read_the_line(p_line, delimiter, p_exiting);
	if (*p_exiting == 1)
		return (ret);
	ret = compare_line(*p_line, p_exiting, delimiter);
	if (*p_exiting == 1)
		return (ret);
	return (0);
}

/* to check :
 *	-> get_next_line fail : DONE -> OK !
 *		-> case error read;
 *		-> case error malloc;
 *	-> here_doc_delimited_by_end_of_file : DONE -> OK !
*/
static int	read_the_line(char **p_line, char *delimiter, int *p_exiting)
{
	int		ret;
	char	*prompt_hd;

	if (isatty(0) == 1)
	{
		prompt_hd = get_prompt_hd(delimiter);
		if (prompt_hd == NULL)
		{
			*p_exiting = 1;
			return (ERROR_MALLOC);
		}
		ret = rl_gnl(p_line, prompt_hd);
		free(prompt_hd);
		if (ret != 0)
		{
			*p_exiting = 1;
			return (ret);
		}
		if (*p_line == NULL)
		{
			*p_exiting = 1;
			ret = here_doc_delimited_by_end_of_file(delimiter);
			if (ret != 0)
			{
				return (ret);
			}
			return (0);
		}
		return (0);
	}
	else
	{
		*p_line = get_next_line(0, &ret);
		return (ret);
	}
}

/* why not just ft_strncmp(line_cmp, delimiter, ft_stlen(line) - 1) ??
 * must be a reason at the time but whatever it works like that 
 * to check
 *	-> ft_strndup fail : DONE ;
*/
static int	compare_line(char *line, int *p_exiting, char *delimiter)
{
	size_t	len_line;
	size_t	len_compare;

	len_line = ft_strlen(line);
	if (line[len_line - 1] == '\n')
		len_compare = len_line - 1;
	else
		len_compare = len_line;
	if (ft_strncmp(line, delimiter, len_compare) == 0)
	{
		*p_exiting = 1;
		free(line);
		return (0);
	}
	return (0);
}

/* to check :
 *	-> here_doc_transform fail : DONE -> OK !
 *	-> write fail : DONE !
*/
/*
static int	transform_write_line(int fd, t_list *env, char *line)
{
	char	*line_cpy;
	int		ret;
	int		nb_write;

	line_cpy = line;
	ret = here_doc_transform(env, &line_cpy);
	free(line);
	if (ret != 0)
		return (ret);
	nb_write = write(fd, line_cpy, ft_strlen(line_cpy));
	free(line_cpy);
	if (nb_write < 0)
	{
		perror("write");
		return (ERROR_WRITE);
	}
	return (0);
}
*/

static int	write_line(int fd, char *line)
{
	size_t	nb_write;

	nb_write = write(fd, line, ft_strlen(line));
	free(line);
	if (nb_write < 0)
	{
		perror("write");
		return (ERROR_WRITE);
	}
	return (0);
}

static char	*get_prompt_hd(char *delimiter)
{
	char	*new_line;

	new_line = ft_strjoin("hd (", delimiter);
	if (new_line == NULL)
		return (new_line);
	new_line = ft_strjoin_free_first(new_line, ") >");
	if (new_line == NULL)
		return (new_line);
	return (new_line);
}
