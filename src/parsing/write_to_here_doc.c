/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:55:20 by jweber            #+#    #+#             */
/*   Updated: 2025/07/14 16:57:19 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

static int	open_fds(char *filename, int *p_fd_tmp_write,	\
										int *p_fd_here_doc_table);
static int	hd_fds_init(t_minishell *p_mini, int *p_fd_tmp_write,	\
														int *p_hd_count);
static int	should_expand(char *delimiter);

/* this function will opens fd for writing to and reading from the here_doc
 * then it will write to the here_doc from user input (and make expansion)
 * then it will close fd for writting and put fd for reading in its right place
 * to check :
 *	-> hd_fds_init fail : TO DO ; -> should be ok but check again
 *	-> get_real_delimiter fail : TO DO ;
 *	-> fill_file_expand fail : TO DO ;
 *	-> fill_file_no_expand fail : TO DO ;
*/
int	write_to_here_doc(t_minishell *p_mini, t_vector *p_tokens, int i,	\
														int *p_hd_count)
{
	int		ret;
	int		fd_tmp_write;
	char	*delimiter;
	int		expanding;

	ret = hd_fds_init(p_mini, &fd_tmp_write, p_hd_count);
	if (ret != 0)
		return (ret);
	delimiter = ((char **)p_tokens->data)[i + 1];
	delimiter = get_real_delimiter(delimiter);
	if (delimiter == NULL)
		return (ERROR_MALLOC);
	expanding = should_expand(delimiter);
	if (expanding == 1)
		ret = fill_file_expand(p_mini->env, fd_tmp_write, delimiter);
	else
		ret = fill_file_no_expand(fd_tmp_write, delimiter);
	free(delimiter);
	if (close (fd_tmp_write) < 0)
		perror(NULL);
	return (ret);
}

/* to check : 
 *	-> generate_hd_filename fail : DONE -> OK !
 *	-> open_fds fail : DONE -> OK !
*/
static int	hd_fds_init(t_minishell *p_mini, int *p_fd_tmp_write,	\
														int *p_hd_count)
{
	char	*filename;
	int		ret;

	ret = generate_hd_filename(&filename, *p_hd_count);
	if (ret != 0)
		return (ret);
	ret = open_fds(filename, p_fd_tmp_write, \
&p_mini->fds_here_doc[*p_hd_count]);
	free(filename);
	return (ret);
}

/* to check
 *	-> first open fail : DONE -> OK !
 *	-> second open fail : DONE -> OK !
 *	-> unlink fail : DONE -> OK !
*/
static int	open_fds(char *filename, int *p_fd_tmp_write,	\
									int *p_fd_here_doc_table)
{
	*p_fd_tmp_write = open(filename, O_WRONLY | O_CREAT, 0666);
	if (*p_fd_tmp_write < 0)
	{
		perror(filename);
		return (ERROR_OPEN);
	}
	*p_fd_here_doc_table = open(filename, O_RDONLY, 0666);
	if (*p_fd_here_doc_table < 0)
	{
		perror(filename);
		if (close(*p_fd_tmp_write) < 0)
			perror("fn: open_fds: close");
		return (ERROR_OPEN);
	}
	if (unlink(filename) < 0)
	{
		perror(filename);
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
