/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:45:27 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/19 19:09:24 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

// free each node of the tree;
static void	free_leaf(t_bintree *leaf)
{
	if (!leaf)
		return ;
	if (leaf->input)
		free(leaf->input);
	if (leaf->cmd)
		free_cmd(leaf->cmd);
	free(leaf);
}

// free the all tree
static void	free_tree(t_bintree *root)
{
	if (!root)
		return ;
	if (root->left)
		free_tree(root->left);
	if (root->right)
		free_tree(root->right);
	free_leaf(root);
	return ;
}

void	free_minishell(t_data *data, int exit_code)
{
	if (data->flag)
		ft_printf(2, "free_minishell with code of exit: %d\n", exit_code);
	free(data->user_input);
	data->user_input = NULL;
	close_fd_tree(data->tree);
	free_tree(data->tree);
	data->tree = NULL;
	free_tabstr(data->paths);
	data->paths = NULL;
	if (exit_code >= 0)
	{
		free_tabstr(data->envp);
		rl_clear_history();
		exit(exit_code);
	}
}

void	free_tabstr(char **tabstr)
{
	size_t	i;

	if (!tabstr)
		return ;
	i = 0;
	while (tabstr[i])
	{
		free(tabstr[i]);
		i++;
	}
	free(tabstr[i]);
	free (tabstr);
}

/* void	free_elem(void *elem, t_mem_type mem) */
/* { */
/* 	t_token	*lst; */
/**/
/* 	if (!elem) */
/* 		return ; */
/* 	lst = elem; */
/* 	if (mem == PTR) */
/* 		free(elem); */
/* 	else if (mem == D_TAB) */
/* 	{ */
/* 		free_tabstr(elem); */
/* 	} */
/* 	else if (mem == LST) */
/* 		ft_lstclear_token(&lst, &free); */
/* } */
