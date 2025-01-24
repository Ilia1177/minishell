/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:36:13 by ilia              #+#    #+#             */
/*   Updated: 2025/01/24 09:55:33 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int sig, siginfo_t *info, void *ctx)
{
	kill(pid, sig, 
}

int	register_signals(struct sigaction *action)
{
	sigemptyset(action.sa_mask);
	action->sa_sigaction = handle_signals;
	action->sa_flags = SA_SIGINFO;

	if (sigaction(SIGINT, action, NULL) == -1)
	{
		ft_printf("sigaction for SIGINT failed");
		return(-1);
	}
	if (sigaction(SIGQUIT, action, NULL) == -1)
	{
		ft_printf("sigaction for SIGQUIT failed");
		return(-1);
	}
	if (sigaction(SIGINT, action, NULL) == -1)
	{
		ft_printf("sigaction for SIGINT failed");
		return(-1);
	}
	return (0);
}

