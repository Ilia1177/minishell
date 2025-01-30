/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:21:45 by jhervoch          #+#    #+#             */
/*   Updated: 2025/01/30 16:35:51 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	arg_len(char *str)
{
	int	len;

	len = 0;
	while (ft_isquote(str[len]))
	{
		ft_skip_quote(&str[len], &len);
	}
	while (str[len] && !is_space(str[len]))
		len++;
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
			ft_skip_quote(&s[i], &i);
		if (s[i])
			i++;
	}
	return (nb_args);
}



static int check_closing_quote(char *str)
{
	char	quote;
	int		close;

	close = 1;
	while (*str)
	{
		if (ft_isquote(*str))
		{
			quote = *str;
			str++;
			while (*str && *str != quote)
				str++;
			if (!*str)
				close = 0;
		}
		if (*str)
			str++;
	}
	return (close);
}

int	syntax_error(char *str)
{
	int	i;

	if (!check_closing_quote(str) || str[0] == '|' || str[0] == '&')
	{
		printf("minishell: syntax error near unexpected token\n");
		return (1);
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			i += ft_strnlen(str, str[i]);
		else if (!ft_strncmp(&str[i], "&|", 2) || !ft_strncmp(&str[i], "|&", 2)
			|| !ft_strncmp(&str[i], "|||", 3) || !ft_strncmp(&str[i], "<<<", 3)
			|| !ft_strncmp(&str[i], ">>>", 3))
		{
			printf("minishell: syntax error near unexpected token\n");
			return (1);
		}
		if (str[i])
			i++;
	}
	return (0);
}
