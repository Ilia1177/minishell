/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:32:20 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/19 18:02:07 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static int	is_option(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 2;
	if (!ft_strncmp(str, "-n", 2))
	{
		while (str[i] == 'n')
			i++;
	}
	else
		return (0);
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	echo(t_bintree *node, t_data *data)
{
	int		i;

	(void)data;
	if (!node->cmd->args)
		return (0);
	i = 1;
	while (is_option(node->cmd->args[i]))
		i++;
	while (node->cmd->args[i])
	{
		ft_printf(node->stdfd[OUT], "%s", node->cmd->args[i]);
		if (node->cmd->args[i + 1])
			ft_printf(node->stdfd[OUT], " ");
		i++;
	}
	if (node->cmd->args[1] && !is_option(node->cmd->args[1]))
		ft_printf(node->stdfd[OUT], "\n");
	else if (!node->cmd->args[1])
		ft_printf(node->stdfd[OUT], "\n");
	data->status = 0;
	return (0);
}
