/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 00:21:43 by npolack           #+#    #+#             */
/*   Updated: 2025/01/29 13:31:41 by npolack          ###   ########.fr       */
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
	//ft_lstiter_token(head, &expand);
	ft_lstiter_token(head, &get_redir); // added by NIL
	ft_lstiter_token(head, &split_args);
	ft_lstiter_token(head, &unquote);
	ft_lst_split_dup(&head, &ft_count_dup, "()");
	free_tabstr(tokens);
	return (head);
}

void unquote(t_token *token)
{
	char	*set;
	int		i;
	char	*str;

	if (token->type != CMD)
		return ;
	i = 0;
	while (token->cmd->args[i])
	{
		str = token->cmd->args[i];
		if (*str == '\'' || *str == '\"')
		{
			if (*str == '\"')
				set = "\"";
			else if (*str == '\'')
				set = "\'";
			token->cmd->args[i] = ft_strtrim(str, set);
			free(str);
		}
		i++;
	}
}


int ft_nb_rdir(char *str)
{
	int	nb_rdir;

	nb_rdir = 0;
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
		{
			str += ft_strnlen(str + 1, *str);
			str ++;
		}
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



// working
// creat an array of rdir null terminated
void	get_redir(t_token *token)
{
	char	*str;
	int		nb_rdir;
	t_rdir	*rdir;
	int		i;
	int		len;

	if (token->type != CMD)
	{
		token->cmd = NULL;
		return ;
	}
	str = token->input;
	nb_rdir = 0;
	nb_rdir = ft_nb_rdir(str);
	rdir = malloc(sizeof(t_rdir) * (nb_rdir + 1));
	if (!rdir)
		return ;
	i = 0;
	len = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			str += ft_strnlen(str + 1, *str);
			str++;
		}
		if (!ft_strncmp(str, "<<", 2))
			str += catch_rdir(rdir, str, HEREDOC, i++);
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
	print_rdir(token);
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
	if (!name)
		return (0);
	ft_strlcpy(name, str + i, len + 1);
	rdir[num_rdir].name = name;
	rdir[num_rdir].type = type;
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
	if (!name)
		return (0);
	ft_strlcpy(name, str + i, len + 1);
	token->cmd->rdir->name = name;
	ft_memset(str, ' ', len + i);
	return (len + i);
}

// not tested
int	catch_heredoc(t_token *token, char *str)
{
	char 	*stop;
	char	*name;
	char	*line;
	int		i;
	int		fd;
	int		len;

	i = 2;
	while (is_space(str[i]))
		i++;
	len = true_wordlen(str + i);
	stop = malloc(sizeof(char) * len + 1);
	if (!stop)
		return (0);
	ft_strlcpy(stop, str, len + 1);
	line = NULL;
	name = random_name(9);
	fd = open(name, O_CREAT | O_WRONLY, 0777);
	while (ft_strcmp(stop, line))
	{
		free(line);
		line = readline(">");
		ft_putendl_fd(line, fd);
	}
	free(line);
	ft_memset(str, ' ', len + i);
	token->cmd->rdir->name = name;
	return (len + i);
}
