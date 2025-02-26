/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:06:30 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/19 18:36:26 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

/****************************************/
/*             TOKENIZE                 */
/****************************************/
//tokenize.c
int			tokenize(t_data *data);

//make_elem.c
t_cmd		*make_cmd(void);
t_token		*make_token(char *str);

//token_utils.c
int			cmd_len(char *str);
int			sep_len(char *str);

//token_tab.c
char		**ft_split_token(char const *s);

#endif
