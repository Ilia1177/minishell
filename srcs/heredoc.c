/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:16:10 by jhervoch          #+#    #+#             */
/*   Updated: 2025/01/27 20:55:22 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_here_doc(char *lim)
{
	char	*str;
	int		fd;

	fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_printf(1, ">");
	str = get_next_line(0);
	lim = ft_strjoin(lim, "\n");
	while (ft_strcmp(str, lim))
	{
		ft_printf(fd, "%s", str);
		free (str);
		str = NULL;
		ft_printf(1, ">");
		str = get_next_line(0);
	}
	free (str);
	free (lim);
	str = NULL;
	close(fd);
}

char	*get_expand(char **env, char *str)
{
	char	*expand;
	int		i;

	expand = NULL;
	i = 0;
	while (env && env[i] && !ft_strncmp(env[i], str + 1, ft_strlen(str + 1)))
		i++;
	if (env && env[i])
		expand = env[i] + ft_strlen(str + 1) + 1;
	return (expand);
}
