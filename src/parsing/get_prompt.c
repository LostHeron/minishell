/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:21:00 by jweber            #+#    #+#             */
/*   Updated: 2025/07/31 18:28:08 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_vectors.h"
#include "ft_standard.h"
#include "ft_string.h"

static void	free_line(t_vector *ptr_vec);
static int	add_error_code_prompt(t_minishell *p_mini, t_vector *p_line);

/* This function should return a pointer to the malloced
 * prompt. 
 *	In case of failure : it should have 
 *	freed all memory allocated in this function
 *	and return NULL
 *	In case of success : return a pointer to the malloced prompt 
*/
char	*get_prompt(t_minishell *p_mini)
{
	int			ret;
	t_vector	line;

	ret = ft_vector_init(&line, 20, sizeof(char), &free_line);
	if (ret != 0)
		return (NULL);
	ret = ft_vector_add_multi(&line,
			p_mini->cwd_name, ft_strlen(p_mini->cwd_name));
	if (ret != 0)
	{
		ft_vector_free(&line);
		return (NULL);
	}
	ret = ft_vector_add_multi(&line, " [ ", 3);
	if (ret != 0)
	{
		ft_vector_free(&line);
		return (NULL);
	}
	ret = add_error_code_prompt(p_mini, &line);
	if (ret != 0)
		return (NULL);
	return (line.data);
}

static void	free_line(t_vector *ptr_vec)
{
	ptr_vec->size = 0;
	free(ptr_vec->data);
	ptr_vec->data = NULL;
}

static int	add_error_code_prompt(t_minishell *p_mini, t_vector *p_line)
{
	char	*nb;
	int		ret;

	nb = ft_itoa(p_mini->last_error_code);
	if (nb == NULL)
	{
		ft_vector_free(p_line);
		return (ERROR_MALLOC);
	}
	ret = ft_vector_add_multi(p_line, nb, ft_strlen(nb));
	free(nb);
	if (ret != 0)
	{
		ft_vector_free(p_line);
		return (ret);
	}
	ret = ft_vector_add_multi(p_line, " ]$ \0", 5);
	if (ret != 0)
	{
		ft_vector_free(p_line);
		return (ret);
	}
	return (0);
}
