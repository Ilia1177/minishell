/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:16:03 by npolack           #+#    #+#             */
/*   Updated: 2025/02/27 12:42:19 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	close_n_init_fd(int *fd)
{
	close(*fd);
	*fd = -1;
}

void	init_fd(t_bintree *node)
{
	node->stdfd[IN] = -1;
	node->stdfd[OUT] = -1;
	node->pipefd[IN] = -1;
	node->pipefd[OUT] = -1;
}

void	close_fd(t_bintree *node)
{
	if (node->stdfd[IN] != -1 && node->stdfd[IN] != -2)
		close_n_init_fd(&node->stdfd[IN]);
	if (node->stdfd[OUT] != -1 && node->stdfd[OUT] != -2)
		close_n_init_fd(&node->stdfd[OUT]);
	if (node->pipefd[IN] != -1 && node->pipefd[IN] != -2)
		close_n_init_fd(&node->pipefd[IN]);
	if (node->pipefd[OUT] != -1 && node->pipefd[OUT] != -2)
		close_n_init_fd(&node->pipefd[OUT]);
}

void	close_fd_tree(t_bintree *node)
{
	if (node->left)
		close_fd_tree(node->left);
	if (node->right)
		close_fd_tree(node->right);
	close_fd(node);
}
