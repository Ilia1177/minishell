/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:18:29 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/06 16:48:34 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnumber(char *str)
{
	if (!ft_isdigit(*str) && *str != '-' && *str != '+')
		return (0);
	str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	format_exit_code(long long number)
{
	int			code;
	long long	nb;

	if (number > 0)
		code = number % 256;
	else
	{
		nb = 256 + number;
		code = (unsigned char) nb;
	}
	return (code);
}

void	exit_number(t_bintree *node)
{
	int			code;
	int			error;
	long long	number;

	error = 0;
	ft_printf(1, "exit\n");
	number = ft_atoller(node->cmd->args[1], &error);
	code = format_exit_code(number);
	if (error)
	{
		ft_printf(2, NR_ARG, node->cmd->args[1]);
		exit(2);
	}
	exit(code);
}

void	exit_minishell(t_bintree *node, t_data *data)
{
	if (!node->cmd->args[1])
	{
		ft_printf(1, "exit\n");
		free_minishell(data);
		exit(0);
	}
	if (ft_isnumber(node->cmd->args[1]) && !node->cmd->args[2])
	{
		exit_number(node);
	}
	else if (ft_isnumber(node->cmd->args[1]) && node->cmd->args[2])
	{
		ft_printf(2, TM_ARG);
		data->status = 1;
	}
	else
	{
		ft_printf(1, "exit\n");
		ft_printf(2, NR_ARG, node->cmd->args[1]);
		exit (2);
	}
}
