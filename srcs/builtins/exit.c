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
	while (is_space(*str))
		str++;
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

/****************************************************
 * exit minishell only if there isnot pipe
 * @param print_code - 1, 2 or 3
 * 1 - print Exit
 * 2 - print NR_ARG
 * 3 - print Exit and NR_ARG
 * @param exit_code is the exit status
 * sent to free_minishell function or Update data->status
 * *************************************************/
int	safe_exit(t_data *data, t_bintree *node, int exit_code, int print_code)
{
	int	has_pipe;

	has_pipe = 0;
	has_pipe = input_has_pipe(data->tree);
	if (print_code == 1 || print_code == 3)
	{
		if (has_pipe)
			ft_printf(node->stdfd[OUT], "exit\n");
		else
			ft_printf(1, "exit\n");
	}
	if (print_code == 2 || print_code == 3)
		ft_printf(2, NR_ARG, node->cmd->args[1]);
	if (!has_pipe)
	{
		close_fd_tree(data->tree);
		free_minishell(data, exit_code);
	}
	return (exit_code);
}

int	exit_number(t_data *data, t_bintree *node)
{
	int			code;
	int			error;
	long long	number;

	error = 0;
	if (node->cmd->rdir == NULL)
		ft_printf(node->stdfd[OUT], "exit\n");
	number = ft_atoller(node->cmd->args[1], &error);
	code = format_exit_code(number);
	if (error)
	{
		safe_exit(data, node, 2, 2);
		return (2);
	}
	safe_exit(data, node, code, 0);
	return (code);
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
		return (safe_exit(data, node, 0, 1));
	if (ft_isnumber(node->cmd->args[1]) && !node->cmd->args[2])
		return (exit_number(data, node));
	else if (ft_isnumber(node->cmd->args[1]) && node->cmd->args[2])
	{
		ft_atoller(node->cmd->args[1], &error);
		if (error)
			return (safe_exit(data, node, 2, 3));
		ft_printf(2, TM_ARG, "exit");
		return (1);
	}
	else
		return (safe_exit(data, node, 2, 3));
	return (1);
}
