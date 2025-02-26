/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_iter_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:31:10 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/19 18:52:10 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "rdir_and_arg.h"
#include "tokenize.h"
#include "parsing.h"

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

// working
// creat an array of rdir null terminated
//token->input = ft_strtrim(str, " ");
//// to be improved (or not) ?? (if redir is in the middle of the args)
//token->input = ft_calloc(1, 1); // if token->input == NULL --> SEGFAULT !!
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
		token->input = ft_strtrim(str, " ");
	else
		token->input = ft_calloc(1, 1);
	free(str);
	rdir[nb_rdir].name = NULL;
	token->cmd->rdir = rdir;
}

/* void	type_token(t_token *token, t_data *data) */
/* { */
/* 	(void)data; */
/* 	if (!ft_strcmp(token->input, "|")) */
/* 		token->type = PIPE; */
/* 	else if (!ft_strcmp(token->input, "||")) */
/* 		token->type = OPERATOR; */
/* 	else if (!ft_strcmp(token->input, "&&")) */
/* 		token->type = OPERATOR; */
/* 	else if (!ft_strcmp(token->input, "(")) */
/* 		token->type = OPERATOR; */
/* 	else if (!ft_strcmp(token->input, ")")) */
/* 		token->type = OPERATOR; */
/* 	else */
/* 	{ */
/* 		token->type = CMD; */
/* 		token->cmd = make_cmd(); */
/* 	} */
/* } */
