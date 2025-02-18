/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:10:42 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/18 14:49:37 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replacing_wildcards(t_token *token, int index, t_list *mfl)
{
	char	**new_args;
	char	**old_args;
	int		nb_arg;

	old_args = token->cmd->args;
	nb_arg = 0;
	while (token->cmd->args[nb_arg])
		nb_arg++;
	nb_arg += ft_lstsize(mfl);
	nb_arg++;
	new_args = ft_calloc(sizeof (char *), nb_arg);
	nb_arg = -1;
	while (++nb_arg < index)
		new_args[nb_arg] =ft_strdup(old_args[nb_arg]);
	while (mfl)
	{
		new_args[nb_arg] = ft_strdup((char *)mfl->content);
		nb_arg++;
		mfl = mfl->next;
	}
	while (old_args[++index])
		new_args[nb_arg++] =ft_strdup(old_args[index]);
	token->cmd->args = new_args;
	return (ft_lstsize(mfl));
}
