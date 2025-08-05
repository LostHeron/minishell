/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 11:08:37 by jweber            #+#    #+#             */
/*   Updated: 2025/08/05 12:08:07 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_string.h"
#include <errno.h>
#include <readline/readline.h>

static int	retrieve_one_line(char **p_line, char **p_line_cursor);

/* this function should :
 *	- return the first line of the user input into *p_line;
 *	- if the variable line_head is NULL it means the user input is empty
 *	  it should then :
 *		- prompt the user for a new line to treat if there is nothing more
 *		to treat
 *		- the prompt showed to the user should be the prompt argument 
 *		passed to the function
 *	- if the variable line_head is not NULL, it means there is still
 *	data to process in line_head, line_cursor remembers at what
 *	point of the line we are and what line we should now return to the user
 *	to check :
 *		readline_fail : TO DO ;
 *		retrieve_one_line faile : TO DO ;
*/
int	rl_gnl(char **p_line, char *prompt)
{
	static char	*line_head;
	static char	*line_cursor;
	int			ret;

	if (line_head == NULL)
	{
		errno = 0;
		line_head = readline(prompt);
		line_cursor = line_head;
		if (errno != 0)
			return (1);
		if (line_head == NULL)
		{
			*p_line = NULL;
			return (0);
		}
	}
	ret = retrieve_one_line(p_line, &line_cursor);
	if (ret != 0)
	{
		free(line_head);
		return (ret);
	}
	if (line_cursor[0] == '\0')
	{
		free(line_head);
		line_head = NULL;
		line_cursor = NULL;
	}
	return (0);
}

/* this function should :
 *	- get the first line from an char* which might contain multiple line
 *	it should get this new line malloc into *p_line variable
 *	and then it should move the *p_line_cursor 
 *	to the start of the following line !
 *	- it searches for a '\n', 
 *		- if it finds one, it duplicates the string
 *		into *p_line from *p_line_cursor to the '\n'
 *		- else it just duplicates the string into *p_line from
 *		*p_line_cursor to the end of *p_line_cursor
 *	
*/
static int	retrieve_one_line(char **p_line, char **p_line_cursor)
{
	char	*new_line_pos;

	new_line_pos = ft_strchr(*p_line_cursor, '\n');
	if (new_line_pos == NULL)
	{
		*p_line = ft_strjoin(*p_line_cursor, "\n");
		if (*p_line == NULL)
			return (ERROR_MALLOC);
		*p_line_cursor = *p_line_cursor + ft_strlen(*p_line_cursor);
	}
	else
	{
		*p_line = ft_strndup(*p_line_cursor, new_line_pos - *p_line_cursor + 1);
		if (*p_line == NULL)
			return (ERROR_MALLOC);
		*p_line_cursor = new_line_pos + 1;
	}
	return (0);
}
