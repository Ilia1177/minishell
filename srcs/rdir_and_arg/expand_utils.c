/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:37:51 by jhervoch          #+#    #+#             */
/*   Updated: 2025/03/01 17:28:49 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "rdir_and_arg.h"

static void	add_quote(char **str, int quote)
{
	char	*requoted;
	char	*tmp;
	char	*old_str;
	char	*quote_to_add;

	old_str = *str;
	if (quote == '\'')
		quote_to_add = "\"";
	else if (quote == '\"')
		quote_to_add = "\'";
	requoted = ft_strjoin(quote_to_add, old_str);
	if (!requoted)
		return ;
	tmp = requoted;
	requoted = ft_strjoin(requoted, quote_to_add);
	free(tmp);
	if (!requoted)
		return ;
	free(old_str);
	*str = requoted;
}

char	*return_expand(t_data *data, char *new_str, char **str, int *i)
{
	char	*value;
	int		flag_free;
	int		j;
	int		quote_inside;

	quote_inside = 0;
	flag_free = 0;
	value = NULL;
	if (*new_str == '?')
		value = catch_expand(data, new_str);
	else if (catch_expand(data, new_str))
		value = ft_strdup(catch_expand(data, new_str));
	j = -1;
	while (value && value[++j])
		if (value[j] == '\"' || value[j] == '\'')
			quote_inside = value[j];
	if (quote_inside)
		add_quote(&value, quote_inside);
	if (*new_str == '?')
		flag_free = 1;
	*i = insert_expand(str, *i + 1, value);
	free(value);
	return (*str);
}
