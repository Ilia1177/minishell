/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 00:21:43 by npolack           #+#    #+#             */
/*   Updated: 2025/01/28 20:57:46 by npolack          ###   ########.fr       */
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
	/* cmd->in_rdir = NULL;	//added by nil */
	/* cmd->out_rdir = NULL;	//added by nil */
	/* cmd->append = NULL;	//added by nil */
	/* cmd->heredoc = NULL;	//added by nil */
	return (cmd);
}

// make a token 
t_token	*make_token(char *str, t_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->input = ft_strdup(str);
	token->type = type;
	token->cmd = NULL;
	token->next = NULL;
	return (token);
}

t_token	*tokenize(char *input)
{
	t_token	*head;
	t_token	*current_token;
	t_token	*previous_token;
	char	**tokens;
	int		i;

	if (!input)
		return (NULL);
	tokens = ft_split_token(input);
	i = 0;
	head = make_token(tokens[i], CMD);
	current_token = head;
	while (tokens[++i])
	{
		previous_token = current_token;
		current_token = make_token(tokens[i], CMD);
		previous_token->next = current_token;
	}
	ft_lstiter_token(head, &type_token);
	ft_lstiter_token(head, &get_redir); // added by NIL
	ft_lstiter_token(head, &split_args);
	ft_lst_split_dup(&head, &ft_count_dup, "()");
	free_tabstr(tokens);
	return (head);
}

int ft_nb_rdir(char *str)
{
	int	nb_rdir;

	nb_rdir = 0;
	while (*str)
	{
		if ((!ft_strncmp(str, "<<", 2)) ||(!ft_strncmp(str, ">>", 2)))
		{
			nb_rdir++;
			str = str + 2;
		}
	   	else if (!ft_strncmp(str, "<", 1) || !ft_strncmp(str, ">", 1))
		{
			nb_rdir++;
			str++;
		}
		else
			str++;
	}
	printf("\n-----nb redir:%d\n", nb_rdir);
	return (nb_rdir);
}

// working
// creat an array of rdir null terminated
void	get_redir(t_token *token)
{
	char	*str;
	int		nb_rdir;
	t_rdir	*rdir;
	int		i;

	str = token->input;
	nb_rdir = 0;
	nb_rdir = ft_nb_rdir(str);
	rdir = malloc(sizeof(t_rdir) * (nb_rdir + 1));
	if (!rdir)
		return ;
	i = 0;
	while (*str)
	{
		if (!ft_strncmp(str, "<<", 2))
			str += catch_rdir(rdir, str, HEREDOC, i++);
		else if (!ft_strncmp(str, ">>", 2))
			str += catch_rdir(rdir, str, APPEND, i++);
	   	else if (!ft_strncmp(str, "<", 1))
			str += catch_rdir(rdir, str, R_IN, i++);
	   	else if (!ft_strncmp(str, ">", 1))
			str += catch_rdir(rdir, str, R_OUT, i++);
		else
			str++;
	}
	rdir[nb_rdir].name = NULL;
	token->cmd->rdir = rdir;
}

int	true_wordlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] && !is_space(str[len]) && !ft_issep(str[len]))
		len++;
	return (len);
}

// working true_wordlen to be replaced
int	catch_rdir(t_rdir	*rdir, char *str, t_type_rdir type, int num_rdir)
{
	char	*name;
	int		i;
	int		len;

	i = 1; 
	if (type == HEREDOC || type == APPEND)
		i++;
	while (is_space(str[i]))
		i++;
	len = true_wordlen(str + i);
	name = malloc(sizeof(char) * len + 1);
	ft_strlcpy(name, str + i, len + 1);
	rdir[num_rdir].name = name;
	rdir[num_rdir].type = type;

	/* if (!ft_strncmp(str, ">", 1)) */
	/* 	token->cmd->rdir->name = name; */
	/* else if (!ft_strncmp(str, "<", 1)) */
	/* 	token->cmd->rdir->name = name; */
	ft_memset(str, ' ', len + i);
	return (len + i);
}

// not tested
int	catch_append(t_token *token, char *str)
{
	char	*name;
	int		i;
	int		len;

	i = 2;
	while (is_space(str[i]))
		i++;
	len = true_wordlen(str + i);
	name = malloc(sizeof(char) * len + 1);
	ft_strlcpy(name, str + i, len + 1);
	token->cmd->rdir->name = name;
	ft_memset(str, ' ', len + i);
	return (len + i);
}

// not tested
int	catch_heredoc(t_token *token, char *str)
{
	char	*name;
	int		i;

	i = 2;
	while (is_space(str[i]))
		i++;
	name = malloc(sizeof(char) * true_wordlen(str + i) + 1);
	ft_strlcpy(name, str, true_wordlen(str + i) + 1);
	token->cmd->rdir->name = name;
	return (i);
}
