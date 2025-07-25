/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_hd_filename.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:54:33 by jweber            #+#    #+#             */
/*   Updated: 2025/07/14 14:37:10 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"
#include "ft_standard.h"
#include "ft_string.h"
#include <limits.h>
#include <unistd.h>

static int	change_name(char **p_filename, size_t *p_nb);

/* to check 
 *	-> ft_itoa fail : DONE -> OK !
 *	-> ft_strjoin fail : DONE -> OK !
 *	-> change_name fail : DONE -> OK !
*/
int	generate_hd_filename(char **p_filename, size_t	nb)
{
	char	*nb_str;
	int		ret;

	nb_str = ft_itoa(nb);
	if (nb_str == NULL)
		return (ERROR_MALLOC);
	*p_filename = ft_strjoin("/tmp/minishell_tmp_file_nb_", nb_str);
	free(nb_str);
	if (*p_filename == NULL)
		return (ERROR_MALLOC);
	while (access(*p_filename, F_OK) == 0)
	{
		ret = change_name(p_filename, &nb);
		if (ret != 0)
			return (ret);
	}
	return (0);
}

/* to check :
 *	-> ERROR *p_nb == INT_MAX : DONE -> OK !
 *	-> ft_itoa fail : DONE -> OK ;
 *	-> ft_strjoin fail : DONE -> OK !
*/
static int	change_name(char **p_filename, size_t *p_nb)
{
	char	*nb_str;

	free(*p_filename);
	if (*p_nb == INT_MAX)
	{
		return (ERROR_HERE_DOC_FILENAME);
	}
	(*p_nb)++;
	nb_str = ft_itoa(*p_nb);
	if (nb_str == NULL)
		return (ERROR_MALLOC);
	*p_filename = ft_strjoin("/tmp/minishell_tmp_file_nb_", nb_str);
	free(nb_str);
	if (*p_filename == NULL)
		return (ERROR_MALLOC);
	return (0);
}
