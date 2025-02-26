/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_supp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:07:33 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/26 20:53:30 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
