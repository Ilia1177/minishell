/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:16:10 by jhervoch          #+#    #+#             */
/*   Updated: 2025/01/29 20:57:11 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_here_doc(char *lim)
{
	char	*str;
	int		fd;
	char	*name;

	name = random_name(10);
	name = ft_strjoin("/tmp/sh-thd-", name);
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (NULL);
	str = listen_to_user("> ");
	while (ft_strcmp(str, lim))
	{
		ft_printf(fd, "%s\n", str);
		free (str);
		str = NULL;
		str = listen_to_user("> ");
	}
	free (str);
	free (lim);
	str = NULL;
	close(fd);
	return (name);
}

char	*catch_expand(t_data *data, char *str)
{
	char	*expand;
	int		i;

	expand = NULL;
	/* if (str) */
	i = 0;
	while (data->envp && data->envp[i] && !ft_strncmp(data->envp[i], str + 1, ft_strlen(str + 1)))
		i++;
	if (data->envp && data->envp[i])
		expand = data->envp[i] + ft_strlen(str + 1) + 1;
	printf("expand =%s\n", expand);
	return (expand);
}

char	*random_name(int nb_char)
{
	int		i;
	int		fd;
	char	buf[1];
	char	*str;

	str = malloc(sizeof(char) * (nb_char + 1));
	fd = open("/dev/urandom", O_RDONLY);
	if (!str || fd == -1)
		return (NULL);
	i = 0;
	while (i < nb_char)
	{
		read(fd, buf, 1);
		buf[0] = buf[0] % 122;
		if ((buf[0] >= 'A' && buf[0] <= 'Z') || (buf[0] >= 'a' && buf[0] <= 'z')
			|| (buf[0] >= '0' && buf[0] <= '9'))
			str[i++] = buf[0];
	}
	str[nb_char] = '\0';
	close(fd);
	return (str);
}
