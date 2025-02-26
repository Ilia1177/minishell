/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:55:34 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/26 21:08:04 by jhervoch         ###   ########.fr       */
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
	char	*input;

	input = listen_to_user(data->prompt);
	if (data->flag)
		ft_printf(2, "get_user_input: out of readline\n");
	if (!input)
	{
		if (data->flag)
			ft_printf(2, "msh: [Ctrl-D]: signal_caught: %d\n", g_signal_caught);
		free_minishell(data, data->status);
	}
	else if (input[0] == 0)
	{
		if (data->flag)
			ft_printf(2, "msh: [ENTER]: signal_caught: %d\n", g_signal_caught);
		data->user_input = input;
		free_minishell(data, -1);
		return (NULL);
	}
	if (!is_all_space(input))
		data->user_input = ft_strtrim(input, "\r\f\v\n\t ");
	free(input);
	return (data->user_input);
}
