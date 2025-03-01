/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:14:17 by jhervoch          #+#    #+#             */
/*   Updated: 2025/03/01 22:29:23 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "rdir_and_arg.h"
#include "parsing.h"

void	free_line(char **line)
{
	char	*str;

	str = *line;
	free(str);
	str = NULL;
}

void	get_lines(char *lim, t_data *data, char **line, int fd)
{
	int		quoted;
	char	*str;

	str = *line;
	quoted = check_lim(&lim);
	while (str && ft_strcmp(str, lim))
	{
		if (!quoted)
			expand_str(data, &str, 1);
		ft_printf(fd, "%s\n", str);
		free(str);
		str = NULL;
		rl_event_hook = event;
		str = readline("> ");
		rl_event_hook = 0;
		if (g_signal_caught == SIGINT)
			break ;
	}
	free(lim);
	*line = str;
}
