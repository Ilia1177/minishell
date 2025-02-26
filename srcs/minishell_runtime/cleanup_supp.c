/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_supp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:07:33 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/26 12:12:24 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	int	is_fd_open(int fd)
//	{
//		char	buffer[1];
//
//		if (read(fd, buffer, 0) == -1)
//		{
//			if (errno == EBADF)
//				return (0);
//		}
//		return (1);
//	}

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
			if (cmd->rdir[i].type == HEREDOC)
			{
				unlink(cmd->rdir[i].name);
				free(cmd->rdir[i].name);
			}
			else
				free(cmd->rdir[i].name);
		}
		free(cmd->rdir);
	}
	free(cmd);
}

//	void	close_all_fd(t_bintree *root)
//	{
//		if (!root)
//			return ;
//		if (root->left)
//			close_all_fd(root->left);
//		if (root->right)
//			close_all_fd(root->right);
//		if (is_fd_open(root->stdfd[IN]))
//			close(root->stdfd[IN]);
//		if (is_fd_open(root->stdfd[OUT]))
//			close(root->stdfd[OUT]);
//		if (is_fd_open(root->pipefd[IN]))
//			close(root->pipefd[IN]);
//		if (is_fd_open(root->pipefd[OUT]))
//			close(root->pipefd[OUT]);
//	}

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
