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

#include "ft_standard.h"
#include "handle_signal.h"
#include "minishell.h"
#include "parsing.h"
#include "ft_string.h"
#include "ft_input.h"
#include <readline/readline.h>
#include <unistd.h>
#include <stdio.h>

static int	rl_here_doc(t_minishell *p_mini, char **p_line, char *delimiter,
				int *p_exiting);
static int	compare_line(char *line, int *p_exiting, char *delimiter);
static int	get_line_compare(char *line, char **p_line_compare);
//static int	read_the_line(char **p_line, char *delimiter, int *p_exiting);
static int	write_line(int fd, char *line);
static char	*get_prompt_hd(char *delimiter);

/* to check
 *	-> gnl_here_doc fail : DONE -> OK!
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
			line_cpy = line;
			ret = here_doc_transform(p_mini->env, &line_cpy);
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
static int	rl_here_doc(t_minishell *p_mini, char **p_line, char *delimiter,
					int *p_exiting)
{
	int		ret;
	char	*prompt;

	/*
	ret = read_the_line(p_line, delimiter, p_exiting);
	if (*p_exiting == 1)
		return (ret);
		*/
	prompt = get_prompt_hd(delimiter);
	if (prompt == NULL)
	{
		*p_exiting = 1;
		return (ERROR_MALLOC);
	}
	get_line(p_mini, p_line, &ret, prompt);
	free(prompt);
	if (ret != 0 || g_my_signal != 0)
	{
		*p_exiting = 1;
		return (ret);
	}
	if (*p_line == NULL)
	{
		*p_exiting = 1;
		ret = here_doc_delimited_by_end_of_file(delimiter);
		return (ret);
	}
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
/*
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
*/

/* why not just ft_strncmp(line_cmp, delimiter, ft_stlen(line) - 1) ??
 * must be a reason at the time but whatever it works like that 
 * to check
 *	-> ft_strndup fail : DONE ;
*/
static int	compare_line(char *line, int *p_exiting, char *delimiter)
{
	int		ret;
	char	*line_compare;

	ret = get_line_compare(line, &line_compare);
	if (ret != 0)
		return (ret);
	ret = ft_strcmp(line_compare, delimiter);
	free(line_compare);
	if (ret == 0)
	{
		*p_exiting = 1;
		free(line);
		return (0);
	}
	return (0);
}

static int	get_line_compare(char *line, char **p_line_compare)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0)
	{
		*p_line_compare = ft_strdup(line);
		if (*p_line_compare == NULL)
			return (ERROR_MALLOC);
		if ((*p_line_compare)[len - 1] == '\n')
			(*p_line_compare)[len - 1] = '\0';
	}
	else
	{
		*p_line_compare = ft_calloc(1, sizeof(char));
		if (*p_line_compare == NULL)
			return (ERROR_MALLOC);
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
	ssize_t	nb_write;

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
