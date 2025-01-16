/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:59:28 by jhervoch          #+#    #+#             */
/*   Updated: 2024/12/19 11:41:02 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_gnl_strdup(const char *s)
{
	char	*new_s;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	new_s = malloc(sizeof(char) * (i + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

static int	check_line(char **stash, char **line)
{
	char	*trim_stash;
	char	*tmp_stash;
	int		i;

	if (!*stash)
		return (0);
	i = 0;
	tmp_stash = *stash;
	while (tmp_stash && tmp_stash[i] != '\0' && tmp_stash[i] != '\n')
		i++;
	if (tmp_stash[i] == '\0')
		return (0);
	if (tmp_stash[i + 1] != '\0')
	{
		trim_stash = &(*stash)[i + 1];
		*stash = ft_gnl_strdup(trim_stash);
		tmp_stash[i + 1] = '\0';
		*line = ft_gnl_strdup(tmp_stash);
		free(tmp_stash);
		return (1);
	}
	*line = ft_gnl_strdup(tmp_stash);
	free(*stash);
	*stash = NULL;
	return (-1);
}

static int	read_input(int fd, char *buf, char **stash, char **line)
{
	int		nb_char;
	char	*tmp_stash;

	nb_char = -1;
	while (nb_char != 0)
	{
		nb_char = read(fd, buf, BUFFER_SIZE);
		if (nb_char == -1)
			return (0);
		buf[nb_char] = '\0';
		if (*stash)
		{
			tmp_stash = *stash;
			*stash = ft_strjoin(tmp_stash, buf);
			free(tmp_stash);
			tmp_stash = NULL;
		}
		else if (nb_char != 0)
			*stash = ft_gnl_strdup(buf);
		if (check_line(stash, line))
			return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char			*buf;
	static char		*stash[1024];
	char			*line;
	int				eol;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	eol = 0;
	line = NULL;
	if (stash[fd])
		if (check_line(&stash[fd], &line))
			return (line);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	eol = read_input(fd, buf, &stash[fd], &line);
	free(buf);
	if (eol == 0)
	{
		line = ft_gnl_strdup(stash[fd]);
		free(stash[fd]);
		stash[fd] = NULL;
	}
	return (line);
}
