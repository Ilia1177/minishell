/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:36:13 by ilia              #+#    #+#             */
/*   Updated: 2025/02/19 18:53:18 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_caught;

void	handle_signals(int sig, siginfo_t *info, void *ctx)
{
	(void)info;
	(void)ctx;
	g_signal_caught = sig;
	if (sig == SIGINT)
	{
		ft_printf(2, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		return ;
}

int	register_signals(void)
{
	struct sigaction	action;

	sigemptyset(&action.sa_mask);
	action.sa_sigaction = handle_signals;
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

/* int	listen_to_signal(t_data *data) */
/* { */
/* 	if (g_signal_caught == SIGQUIT) */
/* 	{ */
/* 		printf("signal %d heard\n", g_signal_caught); */
/* 		printf("SIGQUIT received"); */
/* 		kill(0, SIGQUIT); */
/* 		free_minishell(data); */
/* 		exit(g_signal_caught); */
/* 	} */
/* 	else if (g_signal_caught == SIGINT) */
/* 	{ */
/* 		printf("signal %d heard\n", g_signal_caught); */
/* 		//rl_on_newline(); */
/* 		printf("SIGINT received"); */
/* 		free_minishell(data); */
/* 		init_shell(data); */
/* 		return (1); */
/* 	} */
/* 	return(0); */
/* } */
