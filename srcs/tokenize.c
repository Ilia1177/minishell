/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 00:21:43 by npolack           #+#    #+#             */
/*   Updated: 2025/02/02 10:26:51 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*make_cmd()
{
	t_cmd	*cmd;
	
	cmd = malloc (sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->rdir = NULL;
	return (cmd);
}

t_type	get_type(char *str)
{
	t_type	type;

	if (!ft_strcmp(str, "&"))
		return (-1);
	else if (!ft_strcmp(str, "|"))
		type = PIPE;
	else if (!ft_strcmp(str, "||"))
		type = OPERATOR;
	else if (!ft_strcmp(str, "&&"))
		type = OPERATOR;
	else if (!ft_strcmp(str, "("))
		type = OPERATOR;
	else if (!ft_strcmp(str, ")"))
		type = OPERATOR;
	else
		type = CMD;
	return (type);
}
// make a token 
t_token	*make_token(char *str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->input = str;
	token->type = get_type(str);
	if (token->type == CMD)
		token->cmd = make_cmd();
	else
		token->cmd = NULL;
	token->next = NULL;
	return (token);
}

int	parenthesis_syntax(t_token *prev, t_token *curr)
{
	int	error;

	error = 0;
	if (!ft_strcmp(curr->input, "("))
	{
		if (prev->type == CMD || !ft_strcmp(prev->input, ")"))
			error = 1;
	}
	else if (!ft_strcmp(curr->input, ")"))
	{
		if (!ft_strcmp(prev->input, ")"))
			error = 0;
		else if (prev->type == OPERATOR || prev->type == PIPE)
			error = 1;
	}
	return (error);

}

int	catch_syntax_error(t_token *prev, t_token *curr)
{
	int	error;

	if (!prev || !curr)
		return (-1);
	error = 0;
	if (!ft_strcmp(curr->input, "&"))
		error = 1;
	else if (!ft_strcmp(curr->input, ")") || !ft_strcmp(curr->input, "("))
		error = parenthesis_syntax(prev, curr);
	else if (curr->type == OPERATOR || curr->type == PIPE)
	{
		if (!ft_strcmp(prev->input, ")"))
			error = 0;
		else if (prev->type == PIPE || prev->type == OPERATOR)
			error = 1;
	}	
	else if (curr->type == CMD)
	{
		if (prev->type == CMD || !ft_strcmp(prev->input, ")"))
			error = 1;
	}
	if (error)
		ft_printf(2, "error near expected token '%s'\n", curr->input);
	return (error);
}

t_token	*build_tokenlist(char **tokens)
{
	int		i;
	t_token	*head;
	t_token	*curr_token;
	t_token	*prev_token;

	i = 0;
	head = make_token(tokens[i]);
	if (!head || (head->type != CMD && ft_strcmp(head->input, "(")))
	{
		ft_printf(2, "error near expected token '%s'\n", head->input);
		ft_lstclear_token(&head, &free);
		return (NULL);
	}
	curr_token = head;
	while (tokens[++i])
	{
		prev_token = curr_token;
		curr_token = make_token(tokens[i]);
		if (!curr_token || catch_syntax_error(prev_token, curr_token))
		{
			ft_lstclear_token(&head, &free);
			return (NULL);
		}
		prev_token->next = curr_token;
	}
	free(tokens);
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
	return (-1);
}




int ft_nb_rdir(char *str)
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

int expand_size(char *str, int pos)
{
	int		var_len;

	if (str[pos] == '?')
		return (1);
	var_len = 0;
	while (str[pos + var_len] && ft_isalnum(str[pos + var_len]))
		var_len++;
	return (var_len);
}

int	insert_expand(char **input, int pos, char *exp)
{
	int		var_len;
	int		new_size;
	int		end_size;
	char	*new_input;
	char	*str;

	str = *input;
	var_len = expand_size(str, pos);
	end_size = ft_strlen(str) - var_len - (pos - 1);
	if (exp)
		new_size = pos - 1 + ft_strlen(exp) + end_size + 1;
	else
		new_size = pos - 1 + end_size + 1;
	new_input = malloc(sizeof(char) * new_size);
	ft_strlcpy (new_input, str, pos - 1 + 1);
	if (exp)
		ft_strlcat (new_input, exp, new_size);
	ft_strlcat (new_input, str + pos + var_len, new_size);
	free(str);
	*input = new_input;
	if (exp)
		return (pos - 1 + ft_strlen(exp));
	return (pos - 1);
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

// not tested
int	catch_heredoc(t_rdir *rdir, char *str, t_type_rdir type, int num_rdir)
{
	char	*stop;
	int		i;
	int		len;

	i = 2;
	while (is_space(str[i]))
		i++;
	len = true_wordlen(str + i);
	stop = malloc(sizeof(char) * len + 1);
	if (!stop)
		return (0);
	ft_strlcpy(stop, str + i, len + 1);
	rdir[num_rdir].name = get_here_doc(stop);
	rdir[num_rdir].type = type;
	ft_memset(str, ' ', len + i);
	return (len + i);
}
