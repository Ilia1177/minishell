/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:36:13 by ilia              #+#    #+#             */
/*   Updated: 2025/02/27 12:58:39 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_caught;

void	handle_signals_prompt(int sig, siginfo_t *info, void *ctx)
{
	(void)info;
	(void)ctx;
	if (sig == SIGINT)
	{
		g_signal_caught = sig;
		ft_printf(2, "^C\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		return ;
}

void	handle_signals_exec(int sig, siginfo_t *info, void *ctx)
{
	(void)info;
	(void)ctx;
	g_signal_caught = sig;
	if (sig == SIGINT)
		ft_printf(2, "\n");
	else if (sig == SIGQUIT)
	{
		ft_printf(2, "Quit\n");
		return ;
	}
}

int	register_sig_prompt(void)
{
	struct sigaction	action;

	sigemptyset(&action.sa_mask);
	action.sa_sigaction = handle_signals_prompt;
	action.sa_flags = 0;
	if (sigaction(SIGINT, &action, NULL) == -1)
	{
		printf("sigaction for SIGINT failed");
		return (-1);
	}
	if (sigaction(SIGQUIT, &action, NULL) == -1)
	{
		printf("sigaction for SIGQUIT failed");
		return (-1);
	}
	return (0);
}

int	register_sig_exec(void)
{
	struct sigaction	action;

	sigemptyset(&action.sa_mask);
	action.sa_sigaction = handle_signals_exec;
	action.sa_flags = 0;
	if (sigaction(SIGINT, &action, NULL) == -1)
	{
		printf("sigaction for SIGINT failed");
		return (-1);
	}
	if (sigaction(SIGQUIT, &action, NULL) == -1)
	{
		printf("sigaction for SIGQUIT failed");
		return (-1);
	}
	return (0);
}
