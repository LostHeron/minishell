/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_get_path_len_name.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:17:15 by jweber            #+#    #+#             */
/*   Updated: 2025/06/19 17:59:48 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lists_single.h"
#include "minishell.h"
#include "ft_standard.h"
#include "ft_string.h"
#include "ft_io.h"
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

static int		init_elems_list(char *place_to_go, char ***p_elems, \
														t_list **p_list);
static int		get_list(t_list **p_list, char **elems);
static size_t	get_path_len(t_list *list);
static char		*get_path_name(t_list *list, size_t	path_len);

int	get_path_len_name(char *place_to_go, size_t *p_path_len, \
													char **p_path_name)
{
	int		ret;
	char	**elems;
	t_list	*list;

	ret = init_elems_list(place_to_go, &elems, &list);
	if (ret != 0)
		return (ret);
	*p_path_len = get_path_len(list);
	if (*p_path_len > PATH_NAME_MAX_LENGTH)
	{
		ft_split_free(elems);
		ft_s_lstclear(&list, NULL);
		ft_printf_fd(2, "%s\n", strerror(ENAMETOOLONG));
		return (1);
	}
	*p_path_name = get_path_name(list, *p_path_len);
	if (*p_path_name == NULL)
	{
		ft_split_free(elems);
		ft_s_lstclear(&list, NULL);
		return (ERROR_MALLOC);
	}
	ft_split_free(elems);
	ft_s_lstclear(&list, NULL);
	return (0);
}

static int	get_list(t_list **p_list, char **elems)
{
	size_t	i;
	t_list	*tmp;

	i = 0;
	*p_list = NULL;
	while (elems[i] != NULL)
	{
		if (ft_strcmp(elems[i], "..") == 0)
		{
			ft_s_lstrem_last(p_list, NULL);
		}
		else if (ft_strcmp(elems[i], ".") != 0)
		{
			tmp = ft_s_lstnew(elems[i]);
			if (tmp == NULL)
			{
				ft_s_lstclear(p_list, NULL);
				return (ERROR_MALLOC);
			}
			ft_s_lstadd_back(p_list, tmp);
		}
		i++;
	}
	return (0);
}

static int	init_elems_list(char *place_to_go, char ***p_elems, t_list **p_list)
{
	int	ret;

	*p_elems = ft_split(place_to_go, "/");
	if (*p_elems == NULL)
		return (ERROR_MALLOC);
	ret = get_list(p_list, *p_elems);
	if (ret < 0)
	{
		ft_split_free(*p_elems);
		return (ret);
	}
	return (0);
}

static size_t	get_path_len(t_list *list)
{
	size_t	ret;
	size_t	j;
	size_t	i;

	i = 0;
	ret = 0;
	while (list != NULL)
	{
		j = 0;
		while (((char *)list->content)[j] != '\0')
			j++;
		list = list->next;
		ret += j;
		i++;
	}
	ret += i;
	return (ret);
}

static char	*get_path_name(t_list *list, size_t	path_len)
{
	char	*ret;
	size_t	total_len;

	total_len = path_len + 2;
	ret = ft_malloc(total_len * sizeof(char));
	if (ret == NULL)
		return (NULL);
	ret[0] = '\0';
	while (list != NULL)
	{
		ft_strlcat(ret, "/", total_len);
		ft_strlcat(ret, list->content, total_len);
		list = list->next;
	}
	return (ret);
}
