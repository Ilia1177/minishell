/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:23:44 by npolack           #+#    #+#             */
/*   Updated: 2025/01/20 18:27:25 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_bintree *leaf, char **envp)
{
	int pid;

	pid = fork();
	if (!pid)
	{
		execve(leaf->content[0]
}

int	pipe_operation()
{
	int	pid;

	pid = fork();
	if (!pid)
	
}

int	make_operation(t_bintree *root, char **envp)
{
	if (ft_strcmp(root->content[0], "|"))
		pipe_operation();
	else if (ft_strcmp(root->content[0], "||")
		or_operation();
	else if (ft_strcmp(root->content[0], "&&"))
		and_operation();
}

int	execute_tree(t_bintree *root, char **envp)
{
	if (root->left)
		execute_tree(root->left);

	if (root->type = OPERATOR);
		make_operation(root);
	else if (root->type = CMD)
		exec_cmd(root);


	if (root->right)
		execute_tree(root->right);

}
