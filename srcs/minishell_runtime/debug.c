/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:45:59 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/14 21:30:15 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tree(t_bintree *tree, int space, int start, t_data *data)
{
	int i;

	if (tree == NULL || !data || !data->flag)
		return ;
	space += 5;
	if (!start)
		ft_printf(2, "\n\n----------- Binary tree :  ----\n");
	print_tree(tree->right, space, -1, data);
	ft_printf(2, "\n");
	i = 0;
	while (++i < space)
		ft_printf(2, " ");
	ft_printf(2, "(%s)\n", tree->input);
	print_tree(tree->left, space, -1, data);
	if (!start)
		ft_printf(2, "\n\n-------------------------------\n");
}

void	print_rdir(t_token *token, t_data *data)
{
	int	i;

	if (!data || !data->flag)
		return ;
	ft_printf(2, "\n\n----------- List of tokens is :\n");
	i = 0;
	ft_printf(2, "token %s redir :", token->input);
	while (token->cmd->rdir[i].name)
	{
		ft_printf(2, "name ='%s' type ='%d'\n", token->cmd->rdir[i].name, token->cmd->rdir[i].type);
		i++;
	}
	ft_printf(2, "\n");
}

void	print_list(t_token *list, t_data *data)
{
	int	i;

	if (!list || !data || !data->flag)
		return ;
	
	ft_printf(2, "\n\n\n-------- TOKEN LIST IS----\n");
	i = 0;
	while (list)
	{
		ft_printf(2, "TOKEN nº%d:input = '%s',type = %d", i++, list->input, list->type);
		if (list->type == CMD)
		{
			ft_printf (2, ", args = ");
			print_args(list->cmd->args);
			ft_printf (2, "\n");
		}
		else
			printf("\n");
		/* printf("in_rdir = %6s, out_rdir = %6s, append = %6s, heredoc = %6s\n\n", list->cmd->in_rdir, list->cmd->out_rdir, list->cmd->append, list->cmd->heredoc); */
		list = list->next;
	}
}

// print **arguments for DEBUG
void	print_args(char **args)
{
	int	i;

	if (!args)
	{
		ft_printf(2, "Args Tab = EMPTY\n");
		return ;
	}
	i = 0;
	while (args[i])
	{
		ft_printf(2, "'%s', ", args[i]);
		i++;
	}
}
