/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:16:10 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/04 17:02:03 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_isalnum(buf[0]))
			str[i++] = buf[0];
	}
	str[nb_char] = '\0';
	close(fd);
	return (str);
}

// not tested
int	catch_heredoc(t_rdir *rdir, char *str, t_data *data, int num_rdir)
{
	char	*stop;
	int		i;
	int		len;

	i = 2;
	while (is_space(str[i]))
		i++;
	len = true_wordlen(str + i);
	stop = malloc(sizeof(char) * len + 1);
	if (!stop)
		return (0);
	ft_strlcpy(stop, str + i, len + 1);
	rdir[num_rdir].name = get_here_doc(stop, data);
	rdir[num_rdir].type = HEREDOC;
	ft_memset(str, ' ', len + i);
	return (len + i);
}

char	*get_here_doc(char *lim, t_data *data)
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
		expand_str(data, &str);
		ft_printf(1, "%s\n", str);
		ft_printf(fd, "%s\n", str);
		str = NULL;
		str = listen_to_user("> ");
	}
	free (str);
	free (lim);
	str = NULL;
	close(fd);
	return (name);
}
