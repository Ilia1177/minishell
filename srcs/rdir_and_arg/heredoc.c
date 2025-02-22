/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:16:10 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/19 17:50:04 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "rdir_and_arg.h"
#include "parsing.h"

/****************************************************
 * @random_name
 * return a char str generate with dev/urandom
 * cast in char the buffer to build the string
 * *************************************************/
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

/****************************************************
 * connect the heredoc to the cmd
 * give name
 * type redir
 * *************************************************/
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

int	check_lim(char **old_lim)
{
	int		quoted;
	char	*lim;

	lim = *old_lim;
	quoted = 0;
	if (*lim == '\"' || *lim == '\'')
	{
		quoted = 1;
		lim = remove_quote(lim);
	}
	*old_lim = lim;
	return (quoted);
}

/****************************************************
 * main HEREDOC function
 * create a tmp file with a random_name
 * unlink after exec
 * expand var only if lim is not quoted
 * *************************************************/
char	*get_here_doc(char *lim, t_data *data)
{
	char	*str;
	int		fd;
	char	*name;
	int		quoted;

	name = random_name(10);
	name = ft_strjoin("/tmp/sh-thd-", name);
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (NULL);
	quoted = check_lim(&lim);
	str = listen_to_user("> ");
	while (ft_strcmp(str, lim))
	{
		if (!quoted)
			expand_str(data, &str);
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
