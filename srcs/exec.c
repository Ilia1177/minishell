/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:23:44 by npolack           #+#    #+#             */
/*   Updated: 2025/01/17 16:25:01 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_CMD(t_bintree *leaf, char **envp)
{
	int pid;

	pid = fork();
	if (!pid)
	{
		execve


int	execute_tree(t_bintree *root, char **envp)
{
	if (root->left)
	{
		if (root->type = PIPE
		execute_tree(root->left);
	if (root->right)
		execute_tree(root->right);
	if (root->type = OPERATOR)
		make_operation(root, envp);
	if (root->type = 
}
