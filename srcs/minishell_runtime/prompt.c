/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:55:34 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/26 10:14:50 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get user prompt
char	*listen_to_user(char *prompt)
{
	char	*input;

	/* rl_outstream = stderr; */
	input = readline(prompt);
	if (!input)
		return (NULL);
	add_history(input);
	return (input);
}

char	*get_user_input(t_data *data)
{
	data->user_input = listen_to_user(data->prompt);
	if (data->flag)
		ft_printf(2, "get_user_input: out of readline\n");
	if (!data->user_input)
	{
		if (data->flag)
			ft_printf(2, "msh: [Ctrl-D]: signal_caught: %d\n", g_signal_caught);
		free_minishell(data, data->status);
	}
	else if (data->user_input[0] == 0)
	{
		if (data->flag)
			ft_printf(2, "msh: [ENTER]: signal_caught: %d\n", g_signal_caught);
		free_minishell(data, -1);
		return (NULL);
	}
	return (data->user_input);
}
