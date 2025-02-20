/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:18:29 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/19 17:59:31 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

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

void	exit_number(t_data *data, t_bintree *node)
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
		free_minishell(data, 2);
	}
	free_minishell(data, code);
}

/****************************************************
 * Exit builtins with exit status
 * 1st-[if] whithout arg - exit
 * 2nd-[if] only one arg of number
 * 3rd-[if] first arg is number and has a second
 * 4-[else] more than  one arg and first is not number
 * *************************************************/
int	exit_minishell(t_bintree *node, t_data *data)
{
	int			error;
	
	error = 0;
	if (!node->cmd->args[1])
	{
		ft_printf(1, "exit\n");
		free_minishell(data, 0);
	}
	if (ft_isnumber(node->cmd->args[1]) && !node->cmd->args[2])
	{
		exit_number(data, node);
	}
	else if (ft_isnumber(node->cmd->args[1]) && node->cmd->args[2])
	{
		ft_atoller(node->cmd->args[1], &error);
		if(error)
		{
			ft_printf(2, NR_ARG, node->cmd->args[1]);
			free_minishell(data, 2);
		}
		ft_printf(2, TM_ARG, "exit");
		return (1);
	}
	else
	{
		ft_printf(1, "exit\n");
		ft_printf(2, NR_ARG, node->cmd->args[1]);
		free_minishell(data, 2);
	}
	return (1);
}
