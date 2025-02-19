/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:47:30 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/19 18:50:54 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	ft_lstdelone_token(t_token *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	if (lst->input)
		(*del)(lst->input);
	lst->input = NULL;
	if (lst->cmd)
		free_cmd(lst->cmd);
	free(lst);
}

void	ft_lstclear_token(t_token **lst, void (*del)(void*))
{
	t_token	*previous;
	t_token	*current;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		previous = current;
		current = current->next;
		ft_lstdelone_token(previous, del);
	}
	*lst = NULL;
}

void	iter_split_args(char *input, t_token **iter_token, int nb_args)
{
	int		i;
	t_token	*token;

	token = *iter_token;
	i = 0;
	while (*input && i < nb_args)
	{
		while (is_space(*input))
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
