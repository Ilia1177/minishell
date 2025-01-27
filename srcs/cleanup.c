/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:45:27 by jhervoch          #+#    #+#             */
/*   Updated: 2025/01/27 11:09:48 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_minishell(t_data *data)
{
	free(data->prompt);
	free(data->user_input);
	//close_all_fd(data->tree);			output error in valgrind (not a good idea ?)
	free_tree(data->tree);
	free_tabstr(data->paths);
	free_elem(data->token_list, LST);
	//rl_clear_history(); 				//doesnt work, dont know why (why??)
}

void	free_tabstr(char **tabstr)
{
	size_t	i;

	i = 0;
	if (!*tabstr)
		return ;
	while (tabstr[i])
	{
		free (tabstr[i]);
		++i;
	}
	free (tabstr);
}

void	free_elem(void *elem, t_mem_type mem)
{
	t_token	*lst;

	lst = elem;
	if (mem == PTR)
		free(elem);
	else if (mem == D_TAB)
	{
		free_tabstr(elem);
	}
	else if (mem == LST)
		ft_lstclear_token(&lst, &free);
}

// free each node of the tree;
void	free_leaf(t_bintree *leaf)
{
	int	i;

	if (!leaf)
		return ;
	i = -1;
	while (leaf->content[++i])
		free(leaf->content[i]);
	free(leaf->content[i]);
	free(leaf->content);
	free(leaf);
}

// free the all tree
void	free_tree(t_bintree *root)
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

int	is_fd_open(int fd)
{
	char	buffer[1];

	if (read(fd, buffer, 0) == -1)
	{
		if (errno == EBADF)
			return (0);
	}
	return (1);
}

void	close_all_fd(t_bintree *root)
{
	if (!root)
		return ;
	if (root->left)
		close_all_fd(root->left);
	if (root->right)
		close_all_fd(root->right);
	if (is_fd_open(root->stdfd[IN]))
		close(root->stdfd[IN]);
	if (is_fd_open(root->stdfd[OUT]))
		close(root->stdfd[OUT]);
	if (is_fd_open(root->pipefd[IN]))
		close(root->pipefd[IN]);
	if (is_fd_open(root->pipefd[OUT]))
		close(root->pipefd[OUT]);
}
