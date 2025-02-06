/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:45:27 by jhervoch          #+#    #+#             */
/*   Updated: 2025/01/29 13:55:03 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_minishell(t_data *data)
{
	free(data->prompt);
	free(data->user_input);
	//close_all_fd(data->tree);			output error in valgrind (not a good idea ?)
	free_tree(data->tree);
	free_elem(data->paths, D_TAB);
}

void	free_tabstr(char **tabstr)
{
	size_t	i;

	if (!tabstr || !*tabstr)
		return ;
	i = 0;
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

	if (!elem)
		return ;
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
	if (!leaf)
		return ;
	free(leaf->input);
	free_cmd(leaf->cmd);
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

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	free_tabstr(cmd->args);
	i = -1;
	if (cmd->rdir)
	{
		while (cmd->rdir[++i].name)
		{
			if (cmd->rdir->type == HEREDOC)
				unlink(cmd->rdir[i].name);
			else
				free(cmd->rdir[i].name);
		}
		free(cmd->rdir);
	}
	free(cmd);
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

/* free split when token tab failed*/
void	ft_free_bugsplit(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}
