/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:56:57 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/27 12:58:16 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals_heredoc(int sig, siginfo_t *info, void *ctx)
{
	(void)info;
	(void)ctx;
	if (sig == SIGINT)
	{
		ft_printf(2, "^C");
		g_signal_caught = sig;
		rl_done = 1;
	}
	if (sig == SIGQUIT)
		return ;
}

int	register_sig_heredoc(void)
{
	struct sigaction	action;

	sigemptyset(&action.sa_mask);
	action.sa_sigaction = handle_signals_heredoc;
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
