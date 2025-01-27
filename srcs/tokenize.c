/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 00:21:43 by npolack           #+#    #+#             */
/*   Updated: 2025/01/27 13:13:39 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// make a token 
t_token	*make_token(char *str, t_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->input = ft_strdup(str);
	token->type = type;
	token->cmd = NULL;
	token->next = NULL;
	token->in_rdir = NULL;	//added by nil
	token->out_rdir = NULL;	//added by nil
	token->append = NULL;	//added by nil
	token->heredoc = NULL;	//added by nil
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
		return(NULL);
	tokens = ft_split_token(input);
	print_args(tokens);
	printf("\n");
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

// working
void	get_redir(t_token *token)
{
	char	*str;

	str = token->input;
	if (!str)
		return ;
	while (*str)
	{
		if (!ft_strncmp(str, "<<", 2))
			//str += catch_heredoc(token, str);
			token->heredoc = ft_strdup("oui");
		else if (!ft_strncmp(str, ">>", 2))
			str += catch_append(token, str);
	   	else if (!ft_strncmp(str, "<", 1) || !ft_strncmp(str, ">", 1))
			str += catch_rdir(token, str);
		else
			str++;
	}
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
int	catch_rdir(t_token *token, char *str)
{
	char	*name;
	int		i;
	int		len;

	i = 1;
	while (is_space(str[i]))
		i++;
	len = true_wordlen(str + i);
	name = malloc(sizeof(char) * len + 1);
	ft_strlcpy(name, str + i, len + 1);
	if (!ft_strncmp(str, ">", 1))
		token->out_rdir = name;
	else if (!ft_strncmp(str, "<", 1))
		token->in_rdir = name;
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
	token->append = name;
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
	token->heredoc = name;
	return (i);
}
