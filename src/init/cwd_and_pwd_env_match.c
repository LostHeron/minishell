/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd_and_pwd_env_match.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:33:50 by jweber            #+#    #+#             */
/*   Updated: 2025/07/03 14:36:08 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

static int		init_buf_getcwd(char **p_buf_getcwd);
static int		init_statbufs(struct stat *p_statbuf_pwd, \
			struct stat *p_statbuf_getcwd, char *buf_getcwd, char *value);

/*
 * This function should check if PWD environment variable
 * inode matches the inode of the result of getcwd function
 * Returns :
 * if no errors and both inode matches : return 0;
 * if no errors and both inode do not matches : return positive non null integer
 * in case of errors return a negative non null integer !
*/
int	cwd_and_pwd_env_match(char *value)
{
	struct stat	statbuf_pwd;
	struct stat	statbuf_getcwd;
	int			ret;
	char		*buf_getcwd;

	ret = init_buf_getcwd(&buf_getcwd);
	if (ret != 0)
	{
		return (-1);
	}
	ret = init_statbufs(&statbuf_pwd, &statbuf_getcwd, buf_getcwd, value);
	if (ret != 0)
	{
		return (-1);
	}
	free(buf_getcwd);
	if (statbuf_getcwd.st_ino == statbuf_pwd.st_ino)
		return (0);
	else
		return (1);
}

static int	init_buf_getcwd(char **p_buf_getcwd)
{
	char	*ret_getcwd;

	*p_buf_getcwd = malloc(CWD_NAME_MAX_LENGTH * sizeof(char));
	if (*p_buf_getcwd == NULL)
	{
		return (ERROR_MALLOC);
	}
	ret_getcwd = getcwd(*p_buf_getcwd, CWD_NAME_MAX_LENGTH);
	if (ret_getcwd == NULL)
	{
		free(*p_buf_getcwd);
		perror("fn: getcwd:");
		return (-1);
	}
	return (0);
}

static int	init_statbufs(struct stat *p_statbuf_pwd, \
			struct stat *p_statbuf_getcwd, char *buf_getcwd, char *value)
{
	int	ret;

	ret = stat(value, p_statbuf_pwd);
	if (ret < 0)
	{
		perror("stat:");
		return (-1);
	}
	ret = stat(buf_getcwd, p_statbuf_getcwd);
	if (ret < 0)
	{
		perror("stat:");
		return (-1);
	}
	return (0);
}
