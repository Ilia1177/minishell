/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:36:13 by ilia              #+#    #+#             */
/*   Updated: 2025/01/25 18:13:42 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	signal_caught;

void	handle_signals(int sig, siginfo_t *info, void *ctx)
{
	(void)info;
	(void)ctx;

	signal_caught = sig;
	if (sig == SIGINT)
	{
		ft_putendl_fd(" ^C", 1);
		rl_replace_line("", 0); // Clear the current input
		rl_on_new_line();       // Inform readline to start a new line
		rl_redisplay();         // Redisplay the prompt   
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();       // Inform readline to start a new line
	}
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

int	listen_to_signal(t_data *data)
{
	if (signal_caught == SIGQUIT)
	{
		printf("signal %d heard\n", signal_caught);
		printf("SIGQUIT received");
		kill(0, SIGQUIT);
		free_minishell(data);
		exit(signal_caught);
	}
	else if (signal_caught == SIGINT)
	{
		printf("signal %d heard\n", signal_caught);
		//rl_on_newline();
		printf("SIGINT received");
		free_minishell(data);
		init_shell(data);
		return (1);
	}
	return(0);
}
