/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:46:14 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/26 21:07:18 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/****************************************/
/*               PARSING                */
/****************************************/
//parsing.c
void		ft_lstiter_token(t_data *data, void (*f)(t_token *, t_data *));
int			ft_nb_args(const char *s);
int			arg_len(char *str);

//lst_utils.c
void		ft_lstdelone_token(t_token *lst, void (*del)(void*));
void		ft_lstclear_token(t_token **lst, void (*del)(void*));
void		split_args(t_token *token, t_data *data);

/*****************SYNTAX*****************/
//syntax.c
int			catch_syntax_error(t_token *prev, t_token *curr);

//syntax_utils.c
int			check_closing_quote(char *str);
int			open_parenthesis(char *str);
int			rdir_len(char *str);
int			check_rdir_name(char *str, int *error, int iterator);

/***********QUOTE_UTILS****************/
//quote_utils.c
int			skip_quote(char *str, char quote);
char		find_next_quote(char *str);
char		*get_quotedword(char **str);
char		*get_cleanword(char **str);
char		*remove_quote(char *str);

/*************LST_ITER_FUNC***********/
//lst_iter_func.c
void		unquote_rdir(t_token *token, t_data *data);
void		unquote(t_token *token, t_data *data);
void		get_redir(t_token *token, t_data *data);
void		get_expand(t_token *token, t_data *data);

#endif
