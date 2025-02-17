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

void	print_tree(t_bintree *tree, int space)
{
	if (tree == NULL)
		return ;
	// Increase distance between levels
	int spacing = 5;
	space += spacing;
	// Print the right subtree first
	print_tree(tree->right, space);
	// Print the current node with indentation
	printf("\n");
	for (int i = spacing; i < space; i++)
		printf(" ");
	printf("(%s)\n", tree->input);
	// Print the left subtree
	print_tree(tree->left, space);
}

void	print_rdir(t_token *token)
{
	int	i;

	i = 0;
	ft_printf(2, "token %s redir :", token->input);
	while (token->cmd->rdir[i].name)
	{
		ft_printf(2, "name ='%s' type ='%d'\n", token->cmd->rdir[i].name, token->cmd->rdir[i].type);
		i++;
	}
	ft_printf(2, "\n");
}

void	print_list(t_token *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("TOKEN nº%d:input = '%s',type = %d", i++, list->input, list->type);
		if (list->type == CMD)
		{
			printf (", args = ");
			print_args(list->cmd->args);
			printf ("\n");
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
