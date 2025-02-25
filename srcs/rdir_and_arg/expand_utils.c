/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:37:51 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/25 19:38:29 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "rdir_and_arg.h"

char	*return_expand(t_data *data, char *new_str, char **str, int *i)
{
	char	*value;
	int		flag_free;

	flag_free = 0;
	value = catch_expand(data, new_str);
	if (*new_str == '?')
		flag_free = 1;
	*i = insert_expand(str, *i + 1, value);
	if (flag_free)
		free (value);
	return (*str);
}
