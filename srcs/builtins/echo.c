/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:32:20 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/10 17:35:35 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_bintree *node, t_data *data)
{
	int		i;

	(void)data;
	if (!node->cmd->args)
		return (0);
	i = 1;
	if (node->cmd->args[1] && !ft_strcmp(node->cmd->args[1], "-n"))
		i = 2;
	while (node->cmd->args[i])
	{
		ft_printf(node->stdfd[OUT], "%s", node->cmd->args[i]);
		if (node->cmd->args[i + 1])
			ft_printf(node->stdfd[OUT], " ");
		i++;
	}
	if (node->cmd->args[1] && ft_strcmp(node->cmd->args[1], "-n"))
		ft_printf(node->stdfd[OUT], "\n");
	else if (!node->cmd->args[1])
		ft_printf(node->stdfd[OUT], "\n");
	data->status = 0;
	return (0);
}
