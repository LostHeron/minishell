/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_value_not_null.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:33:50 by jweber            #+#    #+#             */
/*   Updated: 2025/07/18 13:33:52 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_string.h"
#include <ft_standard.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

static int	case_value_is_valid_file(t_minishell *p_mini, char *value);
static int	cwd_and_pwd_env_match(char *value);
static int	init_buf_getcwd(char **p_buf_getcwd);
static int	init_statbufs(struct stat *p_statbuf_pwd,
				struct stat *p_statbuf_getcwd, char *buf_getcwd, char *value);

/* to check : 
 *  -> case_value_is_valid_file fail : DONE -> OK !
 *  -> getcwd fail : DONE -> OK !
 */
int	case_value_not_null(t_minishell *p_mini, char *value)
{
	char	*ret_getcwd;

	if (access(value, F_OK) == 0)
	{
		return (case_value_is_valid_file(p_mini, value));
	}
	else
	{
		ret_getcwd = getcwd(p_mini->cwd_name, CWD_NAME_MAX_LENGTH);
		if (ret_getcwd == NULL)
		{
			perror("fn : initi_cwd_name : getcwd");
			return (-1);
		}
		return (0);
	}
}

/* to check :
 *	-> cwd_and_pwd_env_match fail (return value is negative) : TO DO ;
*/
static int	case_value_is_valid_file(t_minishell *p_mini, char *value)
{
	int		ret;
	char	*ret_getcwd;

	ret = cwd_and_pwd_env_match(value);
	if (ret != 0)
	{
		if (ret > 0)
		{
			ret_getcwd = getcwd(p_mini->cwd_name, CWD_NAME_MAX_LENGTH);
			if (ret_getcwd == NULL)
			{
				perror("fn : case_value_id_valid_file : getcwd");
				return (1);
			}
			return (0);
		}
		else
			return (1);
	}
	else
	{
		ft_strcpy(p_mini->cwd_name, value);
		return (0);
	}
}

/*
 * This function should check if PWD environment variable
 * inode matches the inode of the result of getcwd function
 * Returns :
 * if no errors and both inode matches : return 0;
 * if no errors and both inode do not matches : return positive non null integer
 * in case of errors return a negative non null integer !
 * to check : 
 *	-> init_buf_getcwd fail : DONE -> OK !
 *	-> init_statbufs fail : DONE -> OK !
 *
*/
static int	cwd_and_pwd_env_match(char *value)
{
	struct stat	statbuf_pwd;
	struct stat	statbuf_getcwd;
	int			ret;
	char		*buf_getcwd;

	ret = init_buf_getcwd(&buf_getcwd);
	if (ret != 0)
	{
		return (ret);
	}
	ret = init_statbufs(&statbuf_pwd, &statbuf_getcwd, buf_getcwd, value);
	if (ret != 0)
	{
		free(buf_getcwd);
		return (-1);
	}
	free(buf_getcwd);
	if (statbuf_getcwd.st_ino == statbuf_pwd.st_ino)
		return (0);
	else
		return (1);
}

/* to check : 
 *	-> ft_malloc fail : DONE -> OK !
 *	-> getcwd fail : DONE -> OK !
*/
static int	init_buf_getcwd(char **p_buf_getcwd)
{
	char	*ret_getcwd;

	*p_buf_getcwd = ft_malloc(CWD_NAME_MAX_LENGTH * sizeof(char));
	if (*p_buf_getcwd == NULL)
	{
		return (ERROR_MALLOC);
	}
	ret_getcwd = getcwd(*p_buf_getcwd, CWD_NAME_MAX_LENGTH);
	if (ret_getcwd == NULL)
	{
		perror("fn: init_buf_getcwd: getcwd");
		free(*p_buf_getcwd);
		return (-1);
	}
	return (0);
}

/* to check
 *	-> first stat failure : DONE -> OK !
 *	-> second stat failure : DONE -> OK !
*/
static int	init_statbufs(struct stat *p_statbuf_pwd,
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
