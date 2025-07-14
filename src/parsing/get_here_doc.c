/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:16:57 by jweber            #+#    #+#             */
/*   Updated: 2025/07/01 14:24:52 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "ft_char.h"
#include "ft_string.h"
#include "minishell.h"
#include "ft_io.h"
#include "ft_standard.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static int	get_here_doc_i(t_minishell *p_mini, t_vector *p_tokens, int i, \
														int *p_hd_count);
static int	generate_filename(char **p_filename, int nb);
static int	open_fds(char *filename, int *p_fd_tmp_write, int *p_fd_here_doc_table);
static int	here_doc_delimited_by_end_of_file(char *delimiter);
static int	should_expand(char *delimiter);
static int	fill_file_no_expand(int fd, char *delimiter);
static int	fill_file_expand(t_list *env, int fd, char *delimiter);
static int	here_doc_transform(t_list *env, char **p_line);
static char	*get_key(char *line);
static char	*get_value(t_list *env, char *line);
static void	my_free(t_vector *ptr_vec);

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
			return (ret);
		}
		i++;
	}
	return (0);
}

int	get_here_doc_i(t_minishell *p_mini, t_vector *p_tokens, int i, \
													int *p_hd_count)
{
	char	*delimiter;
	char	*filename;
	int		ret;
	int		fd_tmp_write;

	if (ft_strcmp(((char **)p_tokens->data)[i], "<<") == 0)
	{
		ret = generate_filename(&filename, *p_hd_count);
		if (ret != 0)
		{
			return (ret);
		}
		unlink(filename); // a del this line because generate filename should generate a filename which does not exist already !
		printf("filename = %s\n", filename);
		ret = open_fds(filename, &fd_tmp_write, \
					&p_mini->fds_here_doc[*p_hd_count]);
		free(filename);
		if (ret != 0)
		{
			// close all here_documents 
			return (ret);
		}
		delimiter = ((char **)p_tokens->data)[i + 1];
		if (should_expand(delimiter) == 1)
			fill_file_expand(p_mini->env, fd_tmp_write, delimiter);
		else
			fill_file_no_expand(fd_tmp_write, delimiter);
		if (close (fd_tmp_write) < 0)
		{
			perror(NULL);
			return (1);
		}
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

static int	generate_filename(char **p_filename, int nb)
{
	char	*nb_str;

	nb_str = ft_itoa(nb);
	if (nb_str == NULL)
		return (ERROR_MALLOC);
	*p_filename = ft_strjoin_free_second("/tmp/minishell_tmp_file_nb_", nb_str);
	if (*p_filename == NULL)
	{
		free(nb_str);
	}
	return (0);
}

static int	open_fds(char *filename, int *p_fd_tmp_write, int *p_fd_here_doc_table)
{
	*p_fd_tmp_write = open(filename, O_WRONLY | O_CREAT, 0666);
	if (*p_fd_tmp_write < 0)
	{
		perror("open");
		ft_putstr_fd("could not open filename for writting here_doc!\n", 2);
		return (ERROR_OPEN);
	}
	*p_fd_here_doc_table = open(filename, O_RDONLY, 0666);
	if (*p_fd_here_doc_table < 0)
	{
		perror("open");
		ft_putstr_fd("could not open filename for reading here_doc!\n", 2);
		return (ERROR_OPEN);
	}
	if (unlink(filename) < 0)
	{
		perror("unlink");
		ft_putstr_fd("could not unlink file !\n", 2);
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

static int	fill_file_expand(t_list *env, int fd, char *delimiter)
{
	int		err_code;
	char	*line;
	char	*line_cpy;
	int		ret;

	line = (char *)1;
	while (line != NULL)
	{
		line = get_next_line(0, &err_code);
		if (err_code != 0)
			return (err_code);
		if (line == NULL)
		{
			ret = here_doc_delimited_by_end_of_file(delimiter);
			if (ret != 0)
				return (ERROR_MALLOC);
			return (0);
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			return (0);
		}
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
	}
	return (0);
}

static int	fill_file_no_expand(int fd, char *delimiter)
{
	int		err_code;
	char	*line;
	int		ret;

	while (1)
	{
		line = get_next_line(0, &err_code);
		if (err_code != 0)
			return (err_code);
		if (line == NULL)
		{
			ret = here_doc_delimited_by_end_of_file(delimiter);
			if (ret != 0)
				return (ERROR_MALLOC);
			return (0);
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			return (0);
		}
		if (write(fd, line, ft_strlen(line)) < 0)
		{
			free(line);
			return (ERROR_WRITE);
		}
		free(line);
	}
	return (0);
}

static int	here_doc_transform(t_list *env, char **p_line)
{
	t_vector	vec;
	int			ret;
	size_t		i;
	char		*key;
	char		*value;

	ret = ft_vector_init(&vec, ft_strlen((*p_line)) + 5, \
							sizeof(char), &my_free);
	if (ret != 0)
	{
		return (ret);
	}
	i = 0;
	while ((*p_line)[i])
	{
		while ((*p_line)[i] && (*p_line)[i] != '$')
			i++;
		if ((*p_line)[i] == '$')
		{
			if (ft_isalpha((*p_line)[i + 1]) == 0)
				i++;
			else
			{
				ret = ft_vector_add_multi(&vec, (*p_line), i);
				if (ret != 0)
				{
					ft_vector_free(&vec);
					return (ret);
				}
				key = get_key((*p_line) + i + 1);
				if (key == NULL)
				{
					ft_vector_free(&vec);
					return (ERROR_MALLOC);
				}
				value = get_value(env, key);
				if (value != NULL)
				{
					ret = ft_vector_add_multi(&vec, value, ft_strlen(value));
					if (ret != 0)
					{
						free(key);
						return (ret);
					}
				}
				i += ft_strlen(key) + 1;
				free(key);
				(*p_line) += i;
				i = 0;
			}
		}
	}
	ret = ft_vector_add_multi(&vec, (*p_line), i);
	if (ret != 0)
	{
		ft_vector_free(&vec);
		return (ret);
	}
	((char *)vec.data)[vec.size] = '\0';
	(*p_line) = vec.data;
	return (0);
}

static void	my_free(t_vector *ptr_vec)
{
	free(ptr_vec->data);
	return ;
}

static char	*get_key(char *line)
{
	size_t	i;
	char	*res;

	i = 0;
	while (line[i] && ft_isalnum(line[i]) != 0)
	{
		i++;
	}
	res = ft_strndup(line, i);
	return (res);
}

static char	*get_value(t_list *env, char *key)
{
	if (env == NULL)
		return (NULL);
	while (env != NULL)
	{
		if (ft_strcmp(((t_env *)env->content)->key, key) == 0)
			return (((t_env *)env->content)->value);
		env = env->next;
	}
	return (NULL);
}

static int	here_doc_delimited_by_end_of_file(char *delimiter)
{
	char	*str;

	str = ft_strjoin("warning: here-document delimited \
							by end-of-file (wanted `", delimiter);
	if (str == NULL)
		return (ERROR_MALLOC);
	str = ft_strjoin_free_first(str, "')");
	if (str == NULL)
		return (ERROR_MALLOC);
	ft_putstr_fd(str, 2);
	free(str);
	return (0);
}
