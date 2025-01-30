/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_iter_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:31:10 by jhervoch          #+#    #+#             */
/*   Updated: 2025/01/30 16:35:45 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void unquote(t_token *token, t_data *data)
{
	int		j;
	char	*str;
	char	*new_arg;
	int		len;

	(void)data;
	if (token->type != CMD)
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
	int		i;
	char	*str;
	char	*exp;
	int		quoted;

	str = token->input;
	i = -1;
	quoted = -1;
	while (str[++i])
	{
		if (str[i] == '\"')
			quoted *= -1;
		else if (str[i] == '\'' && quoted < 0)
		{
			i++;
			i += ft_strnlen(&str[i], '\'');
		}
		else if (str[i] == '$')
		{
			exp = catch_expand(data, &str[i + 1]);
			i = insert_expand(&token->input, i + 1, exp);
			str = token->input;
		}
	}
}

// working
// creat an array of rdir null terminated
void	get_redir(t_token *token,t_data *data)
{
	char	*str;
	int		nb_rdir;
	t_rdir	*rdir;
	int		i;

	(void)data;
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
	i = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			str += skip_quote(str, *str);
		if (!ft_strncmp(str, "<<", 2))
			str += catch_heredoc(rdir, str, HEREDOC, i++);
		else if (!ft_strncmp(str, ">>", 2))
			str += catch_rdir(rdir, str, APPEND, i++);
	   	else if (!ft_strncmp(str, "<", 1))
			str += catch_rdir(rdir, str, R_IN, i++);
	   	else if (!ft_strncmp(str, ">", 1))
			str += catch_rdir(rdir, str, R_OUT, i++);
		else if (*str)
			str++;
	}
	rdir[nb_rdir].name = NULL;
	token->cmd->rdir = rdir;
}

void	split_args(t_token *token, t_data *data)
{
	int		nb_args;
	int		i;
	char	*input;

	(void)data;
	if (token->type == CMD)
	{
		input = token->input;
		i = 0;
		nb_args = ft_nb_args(token->input);
		token->cmd->args = ft_calloc(nb_args + 1, sizeof(char *));
		if (!token->cmd->args)
			return ;
		while (*input && i < nb_args)
		{
			while (*input && is_space(*input) && !ft_isquote(*input))
				input++;
			token->cmd->args[i] = ft_calloc(arg_len(input) + 1, sizeof(char));
			if (!token->cmd->args[i])
			{
				ft_free_bugsplit(token->cmd->args, i - 1);
				return ;
			}
			ft_strlcpy(token->cmd->args[i], input, arg_len(input) + 1);
			input += arg_len(input);
			i++;
		}
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
