/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:16:57 by jweber            #+#    #+#             */
/*   Updated: 2025/07/14 14:51:21 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_standard.h"
#include "ft_string.h"
#include "ft_vectors.h"
#include "minishell.h"
#include "parsing.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static int	get_here_doc_i(t_minishell *p_mini, t_vector *p_tokens, int i, \
														int *p_hd_count);
static int	open_fds(char *filename, int *p_fd_tmp_write, \
										int *p_fd_here_doc_table);
static int	should_expand(char *delimiter);
static int	write_to_here_doc(t_minishell *p_mini, t_vector *p_tokens, int i, \
														int *p_hd_count);

/* main function of here_doc
 * if an error occurs when calling get_here_doc_i,
 * the function should then free / close everything related to 
 * heredoc and return an error corresponding to the problem
*/
int	get_here_doc(t_minishell *p_mini, t_vector *p_tokens)
{
	size_t	i;
	int		ret;
	int		hd_count;

	i = 0;
	hd_count = 0;
	while (i < p_tokens->size)
	{
		ret = get_here_doc_i(p_mini, p_tokens, i, &hd_count);
		if (ret != 0)
		{
			// do somehting ?
			// close all here_documents ?
			return (ret);
		}
		i++;
	}
	return (0);
}

int	get_here_doc_i(t_minishell *p_mini, t_vector *p_tokens, int i, \
													int *p_hd_count)
{
	if (ft_strcmp(((char **)p_tokens->data)[i], "<<") == 0)
	{
		write_to_here_doc(p_mini, p_tokens, i, p_hd_count);
		/*
		ret = generate_filename(&filename, *p_hd_count);
		if (ret != 0)
		{
			return (ret);
		}
		ret = open_fds(filename, &fd_tmp_write, \
					&p_mini->fds_here_doc[*p_hd_count]);
		free(filename);
		if (ret != 0)
			return (ret);
		delimiter = ((char **)p_tokens->data)[i + 1];
		if (should_expand(delimiter) == 1)
			fill_file_expand(p_mini->env, fd_tmp_write, delimiter);
		else
			fill_file_no_expand(fd_tmp_write, delimiter);
		if (close (fd_tmp_write) < 0)
			perror(NULL);
		*/
		free(((char **)p_tokens->data)[i + 1]);
		((char **)p_tokens->data)[i + 1] = ft_malloc(2 * sizeof(char));
		if (((char **)p_tokens->data)[i + 1] == NULL)
		{
			// do other stuff ?
			return (ERROR_MALLOC);
		}
		((char **)p_tokens->data)[i + 1][0] = *p_hd_count;
		((char **)p_tokens->data)[i + 1][1] = '\0';
		(*p_hd_count)++;
	}
	return (0);
}

static int	write_to_here_doc(t_minishell *p_mini, t_vector *p_tokens, int i, \
														int *p_hd_count)
{
	char	*filename;
	int		ret;
	int		fd_tmp_write;
	char	*delimiter;
	int		expanding;

	ret = generate_hd_filename(&filename, *p_hd_count);
	if (ret != 0)
		return (ret);
	ret = open_fds(filename, &fd_tmp_write, \
				&p_mini->fds_here_doc[*p_hd_count]);
	free(filename);
	if (ret != 0)
		return (ret);
	delimiter = ((char **)p_tokens->data)[i + 1];
	expanding = should_expand(delimiter);
	delimiter = get_real_delimiter(delimiter);
	if (delimiter == NULL)
	{
		if (close (fd_tmp_write) < 0)
			perror(NULL);
		return (ERROR_MALLOC);
	}
	if (expanding == 1)
		fill_file_expand(p_mini->env, fd_tmp_write, delimiter);
	else
		fill_file_no_expand(fd_tmp_write, delimiter);
	free(delimiter);
	if (close (fd_tmp_write) < 0)
		perror(NULL);
	return (0);
}

static int	open_fds(char *filename, int *p_fd_tmp_write, \
									int *p_fd_here_doc_table)
{
	*p_fd_tmp_write = open(filename, O_WRONLY | O_CREAT, 0666);
	if (*p_fd_tmp_write < 0)
	{
		perror("open");
		return (ERROR_OPEN);
	}
	*p_fd_here_doc_table = open(filename, O_RDONLY, 0666);
	if (*p_fd_here_doc_table < 0)
	{
		perror("open");
		if (close(*p_fd_tmp_write) < 0)
			perror("fn: open_fds: close");
		return (ERROR_OPEN);
	}
	if (unlink(filename) < 0)
	{
		perror("unlink");
		if (close(*p_fd_tmp_write) < 0)
			perror("fn: open_fds: close");
		if (close(*p_fd_here_doc_table) < 0)
			perror("fn: open_fds: close");
		return (ERROR_UNLINK);
	}
	return (0);
}

static int	should_expand(char *delimiter)
{
	size_t	i;

	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '\'' || delimiter[i] == '\"')
			return (0);
		i++;
	}
	return (1);
}
