/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 00:21:43 by npolack           #+#    #+#             */
/*   Updated: 2025/02/04 19:52:52 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*build_tokenlist(char **tokens)
{
	int		i;
	t_token	*head;
	t_token	*curr_token;
	t_token	*prev_token;

	i = 0;
	head = make_token(tokens[i]);
	if (!head)
		return (NULL);
	if (head->type != CMD && ft_strcmp(head->input, "("))
	{
		ft_printf(2, "SYNTERR '%s'\n", head->input);
		ft_lstclear_token(&head, &free);
		return (NULL);
	}
	curr_token = head;
	while (tokens[++i])
	{
		prev_token = curr_token;
		curr_token = make_token(tokens[i]);
		prev_token->next = curr_token;
		if (!curr_token || catch_syntax_error(prev_token, curr_token))
		{
			ft_lstclear_token(&head, &free);
			return (NULL);
		}
	}
	return (head);
}

int	tokenize(t_data *data)
{
	char	**tokens;

	if (!data->user_input)
		return (0);
	tokens = ft_split_token(data->user_input);
	if (!tokens)
		return (0);
	data->token_list = build_tokenlist(tokens);
	if (!data->token_list)
	{
		free_tabstr(tokens);
		return (0);
	}
	ft_lstiter_token(data, &get_redir);
	ft_lstiter_token(data, &get_expand);
	ft_lstiter_token(data, &split_args);
	ft_lstiter_token(data, &unquote);
	return (1);
}

int	ft_nb_rdir(char *str)
{
	int	nb_rdir;

	nb_rdir = 0;
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
			str += skip_quote(str, *str);
		if ((!ft_strncmp(str, "<<", 2)) || (!ft_strncmp(str, ">>", 2)))
		{
			nb_rdir++;
			str = str + 2;
		}
		else if (!ft_strncmp(str, "<", 1) || !ft_strncmp(str, ">", 1))
		{
			nb_rdir++;
			str++;
		}
		else if (*str)
			str++;
	}
	return (nb_rdir);
}

int	true_wordlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] && !is_space(str[len]) && !ft_issep(str[len]))
	{
		if (str[len] == '<' || str[len] == '>')
			return (len);
		len++;
	}
	return (len);
}

// working true_wordlen to be replaced
int	catch_rdir(t_rdir *rdir, char *str, t_type_rdir type, int num_rdir)
{
	char	*name;
	int		i;
	int		len;

	i = 1;
	if (type == APPEND)
		i++;
	while (is_space(str[i]))
		i++;
	len = true_wordlen(str + i);
	name = malloc(sizeof(char) * len + 1);
	if (!name)
		return (0);
	ft_strlcpy(name, str + i, len + 1);
	rdir[num_rdir].name = name;
	rdir[num_rdir].type = type;
	ft_memset(str, ' ', len + i);
	return (len + i);
}
