/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:41:09 by cviel             #+#    #+#             */
/*   Updated: 2025/08/19 18:17:09 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "expand.h"
#include "ft_vectors.h"
#include "ft_string.h"
#include "ft_standard.h"

/* malloc -> OK */
int	remove_last(t_exp *p_exp_part, size_t p_ind)
{
	char	*replace;

	replace = malloc(sizeof(char) * (p_ind + 1));
	if (replace == NULL)
		return (ERROR_MALLOC);
	ft_strncpy(replace, p_exp_part->content, p_ind);
	replace[p_ind] = '\0';
	free(p_exp_part->content);
	p_exp_part->content = replace;
	return (0);
}

/*	malloc -> OK */
int	replace_key_value(t_exp *p_exp_part, size_t *p_ind,
	size_t len_key, t_env *p_env)
{
	char	*replace;
	size_t	len_replace;
	size_t	len_val;

	if (p_env == NULL || p_env->value == NULL)
		len_val = 0;
	else
		len_val = ft_strlen(p_env->value);
	len_replace = ft_strlen(p_exp_part->content) - (len_key + 1) + len_val + 1;
	replace = malloc(sizeof(char) * len_replace);
	if (replace == NULL)
		return (ERROR_MALLOC);
	*replace = '\0';
	ft_strncat(replace, p_exp_part->content, *p_ind);
	if (p_env != NULL && p_env->value != NULL)
		ft_strlcat(replace, p_env->value, len_replace);
	ft_strlcat(replace, p_exp_part->content + *p_ind + len_key + 1,
		len_replace);
	free(p_exp_part->content);
	p_exp_part->content = replace;
	*p_ind += len_val;
	return (0);
}

/*	ft_itoa -> OK
	malloc -> OK */
int	replace_err_code(t_exp *p_exp_part, size_t *p_ind, t_minishell mini)
{
	char	*replace;
	char	*err_code;
	size_t	len_replace;
	size_t	len_code;

	err_code = ft_itoa(mini.last_error_code);
	if (err_code == NULL)
		return (ERROR_MALLOC);
	len_code = ft_strlen(err_code);
	len_replace = ft_strlen(p_exp_part->content) - 2 + len_code + 1;
	replace = malloc(sizeof(char) * len_replace);
	if (replace == NULL)
	{
		free(err_code);
		return (ERROR_MALLOC);
	}
	*replace = '\0';
	ft_strncat(replace, p_exp_part->content, *p_ind);
	ft_strlcat(replace, err_code, len_replace);
	free(err_code);
	ft_strlcat(replace, p_exp_part->content + *p_ind + 2, len_replace);
	free(p_exp_part->content);
	p_exp_part->content = replace;
	*p_ind += len_code;
	return (0);
}
