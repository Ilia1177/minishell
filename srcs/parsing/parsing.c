/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:21:45 by jhervoch          #+#    #+#             */
/*   Updated: 2025/03/01 21:00:18 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	ft_lstiter_token(t_data *data, void (*f)(t_token *, t_data *))
{
	t_token	*iterator;

	if (!data->token_list || !f)
		return ;
	iterator = data->token_list;
	while (iterator)
	{
		(*f)(iterator, data);
		iterator = iterator->next;
	}
}

int	count_args(char **str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	arg_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] && !is_space(str[len]))
	{
		if (ft_isquote(str[len]))
			len += skip_quote(str + len, str[len]);
		else
			len++;
	}
	return (len);
}

int	ft_nb_args(const char *s)
{
	int	nb_args;
	int	i;

	nb_args = 0;
	i = 0;
	while (s[i])
	{
		if (i == 0 && !is_space(s[i]))
			nb_args++;
		else if (!is_space(s[i]) && is_space(s[i - 1]))
			nb_args++;
		while (ft_isquote(s[i]))
			i += skip_quote((char *)s + i, s[i]);
		if (s[i])
			i++;
	}
	return (nb_args);
}
