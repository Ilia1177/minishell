/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:11:19 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/10 20:00:24 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_nb_rdir(char *str)
{
	int	nb_rdir;

	nb_rdir = 0;
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
			str += skip_quote(str, *str);
		if ((!ft_strncmp(str, "<<", 2)) || (!ft_strncmp(str, ">>", 2)))
		{
			nb_rdir++;
			str = str + 2;
		}
		else if (!ft_strncmp(str, "<", 1) || !ft_strncmp(str, ">", 1))
		{
			nb_rdir++;
			str++;
		}
		else if (*str)
			str++;
	}
	return (nb_rdir);
}

int	true_wordlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] && !is_space(str[len]) && !ft_issep(str[len]))
	{
		if (ft_isquote(str[len]))
			len += skip_quote(str + len, str[len]);
		else if (str[len] == '<' || str[len] == '>')
			return (len);
		else
			len++;
	}
	return (len);
}

void	seek_rdir(char *str, t_rdir **s_rdir, t_data *data)
{
	int		i;
	t_rdir	*rdir;

	rdir = *s_rdir;
	i = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			str += skip_quote(str, *str);
		if (!ft_strncmp(str, "<<", 2))
			str += catch_heredoc(rdir, str, data, i++);
		else if (!ft_strncmp(str, ">>", 2))
			str += catch_rdir(rdir, str, APPEND, i++);
		else if (!ft_strncmp(str, "<", 1))
			str += catch_rdir(rdir, str, R_IN, i++);
		else if (!ft_strncmp(str, ">", 1))
			str += catch_rdir(rdir, str, R_OUT, i++);
		else if (*str)
			str++;
	}
}

// working true_wordlen to be replaced
int	catch_rdir(t_rdir *rdir, char *str, t_type_rdir type, int num_rdir)
{
	char	*name;
	int		i;
	int		len;

	i = 1;
	if (type == APPEND)
		i++;	
	while (is_space(str[i]))
		i++;
	len = true_wordlen(str + i);
	name = malloc(sizeof(char) * len + 1);
	if (!name)
		return (0);
	ft_strlcpy(name, str + i, len + 1);
	rdir[num_rdir].name = name;
	rdir[num_rdir].type = type;
	ft_memset(str, ' ', len + i);
	return (len + i);
}
