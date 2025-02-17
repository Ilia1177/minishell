/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_iter_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:31:10 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/14 21:09:01 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unquote_rdir(t_token *token, t_data *data)
{
	int		j;
	char	*str;
	char	*new_rdir;
	int		len;

	(void)data;
	if (token->type != CMD || !token->cmd || !token->cmd->rdir)
		return ;
	j = 0;
	while (token->cmd->rdir[j].name)
	{
		str = token->cmd->rdir[j].name;
		len = ft_strlen(str);
		if (ft_strnstr(str, "\"", len) || ft_strnstr(str, "\'", len))
		{
			new_rdir = remove_quote(str);
			token->cmd->rdir[j].name = new_rdir;
			free(str);
		}
		j++;
	}
}

void	unquote(t_token *token, t_data *data)
{
	int		j;
	char	*str;
	char	*new_arg;
	int		len;

	(void)data;
	if (token->type != CMD || !token->cmd)
		return ;
	j = 0;
	while (token->cmd->args[j])
	{
		str = token->cmd->args[j];
		len = ft_strlen(str);
		if (ft_strnstr(str, "\"", len) || ft_strnstr(str, "\'", len))
		{
			new_arg = remove_quote(str);
			token->cmd->args[j] = new_arg;
			free(str);
		}
		j++;
	}
}

void	get_expand(t_token *token, t_data *data)
{
	expand_str(data, &token->input);
}

int	is_all_space(char *str)
{
	int	i;
	int	is_all_space;

	is_all_space = 1;
	i = 0;
	while (str[i])
	{
		if (!isspace(str[i]))
			is_all_space = 0;
		i++;
	}
	return (is_all_space);
}
// working
// creat an array of rdir null terminated
void	get_redir(t_token *token, t_data *data)
{
	char	*str;
	int		nb_rdir;
	t_rdir	*rdir;

	if (token->type != CMD)
	{
		token->cmd = NULL;
		return ;
	}
	str = token->input;
	nb_rdir = ft_nb_rdir(str);
	rdir = malloc(sizeof(t_rdir) * (nb_rdir + 1));
	if (!rdir)
		return ;
	seek_rdir(str, &rdir, data);
	if (!is_all_space(str))
		token->input = ft_strtrim(str, " "); // to be improved (or not) ?? (if redir is in the middle of the args)
	else
		token->input = ft_calloc(1, 1); // if token->input == NULL --> SEGFAULT !!
	free(str);
	rdir[nb_rdir].name = NULL;
	token->cmd->rdir = rdir;
}

void	split_args(t_token *token, t_data *data)
{
	int		nb_args;
	char	*input;

	(void)data;
	if (token->type == CMD && token->cmd)
	{
		input = token->input;
		nb_args = ft_nb_args(token->input);
		token->cmd->args = ft_calloc(nb_args + 1, sizeof(char *));
		if (!token->cmd->args)
			return ;
		iter_split_args(input, &token, nb_args);
	}
}

void	type_token(t_token *token, t_data *data)
{
	(void)data;
	if (!ft_strcmp(token->input, "|"))
		token->type = PIPE;
	else if (!ft_strcmp(token->input, "||"))
		token->type = OPERATOR;
	else if (!ft_strcmp(token->input, "&&"))
		token->type = OPERATOR;
	else if (!ft_strcmp(token->input, "("))
		token->type = OPERATOR;
	else if (!ft_strcmp(token->input, ")"))
		token->type = OPERATOR;
	else
	{
		token->type = CMD;
		token->cmd = make_cmd();
	}
}
