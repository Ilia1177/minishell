/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:13:53 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/25 19:38:38 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "rdir_and_arg.h"

static int	expand_size(char *str, int pos)
{
	int		var_len;

	if (str[pos] == '?')
		return (1);
	var_len = 0;
	while (str[pos + var_len] && (ft_isalnum(str[pos + var_len])
			|| str[pos + var_len] == '_'))
		var_len++;
	return (var_len);
}

int	insert_expand(char **input, int pos, char *exp)
{
	int		var_len;
	int		new_size;
	int		end_size;
	char	*new_input;
	char	*str;

	str = *input;
	var_len = expand_size(str, pos);
	end_size = ft_strlen(str) - var_len - (pos - 1);
	if (exp)
		new_size = pos - 1 + ft_strlen(exp) + end_size + 1;
	else
		new_size = pos - 1 + end_size + 1;
	new_input = malloc(sizeof(char) * new_size);
	ft_strlcpy (new_input, str, pos - 1 + 1);
	if (exp)
		ft_strlcat (new_input, exp, new_size);
	ft_strlcat (new_input, str + pos + var_len, new_size);
	free(str);
	*input = new_input;
	if (exp)
		return (pos - 1 + ft_strlen(exp));
	return (pos - 1);
}

/*******************************************************
 * seek the $ in *str and return his index
 * return -1 if not found
 * *****************************************************/
static int	find_expand(char *str)
{
	int	i;
	int	quoted;

	i = -1;
	quoted = -1;
	while (str[++i])
	{
		if (str[i] == '\"')
			quoted *= -1;
		else if (str[i] == '\'' && quoted < 0)
		{
			i++;
			i += ft_strnlen(&str[i], '\'');
		}
		else if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1])
				|| str[i + 1] == '?' || (ft_isquote(str[i + 1]) && quoted < 0)))
			return (i);
	}
	return (-1);
}

/*******************************************************
 * get value of ENV 
 * +1 is to skip =
 * checks that the string is followed by = 
 * to not  return variables that start with the same string
******************************************************/
char	*catch_expand(t_data *data, char *str)
{
	char	*expand;
	int		i;
	int		len;

	if (str[0] == '?')
		return (ft_itoa(data->status));
	expand = NULL;
	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	i = 0;
	while (data->envp && data->envp[i] && ft_strncmp(data->envp[i], str, len))
		i++;
	if (data->envp && data->envp[i] && data->envp[i][len] == '=')
		expand = data->envp[i] + len + 1;
	return (expand);
}

/*******************************************************
 	* expand ENV value of token->input
 	* realloc the str input
******************************************************/
void	expand_str(t_data *data, char **str)
{
	char	*new_str;
	int		i;
	int		size;

	new_str = *str;
	while (*new_str)
	{
		i = find_expand(new_str);
		if (i == -1 || is_space(new_str[i + 1]) || !new_str[i + 1])
			return ;
		if ((new_str[i + 1] == '\'' || new_str[i + 1] == '\"'))
		{
			size = ft_strlen(new_str);
			new_str[i] = '\0';
			ft_strlcat(new_str, new_str + i + 1, size);
		}
		else
		{
			new_str = return_expand(data, &new_str[i + 1], str, &i);
		}
	}
}
