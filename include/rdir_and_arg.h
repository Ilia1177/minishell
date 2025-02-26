/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir_and_arg.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:34:48 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/25 19:40:06 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RDIR_AND_ARG_H
# define RDIR_AND_ARG_H

/****************************************/
/*               RDIR_&&_ARG            */
/****************************************/

/***********EXPAND****************/
//expand.c
int		insert_expand(char **input, int pos, char *exp);
char	*catch_expand(t_data *data, char *str);
void	expand_str(t_data *data, char **str);

//expand_utils.c
char	*return_expand(t_data *data, char *new_str, char **str, int *i);

/***********HEREDOC****************/
//heredoc.c
char	*get_here_doc(char *lim, t_data *data);
int		catch_heredoc(t_rdir *rdir, char *str, t_data *data, int num_rdir);

/***********RDIR****************/
//redir.c
int		ft_nb_rdir(char *str);
int		true_wordlen(char *str);
void	seek_rdir(char *str, t_rdir **s_rdir, t_data *data);

/***********WILDCARDS****************/
//wildcards.c
void	wildcards(t_token *token, t_data *data);
void	sort_list_dir(t_list **list);

//wildcards_search.c
int		middle_search(char **file_str, char *pattern_str, int *nb_find);
int		end_search(char **file_str, char *pattern_str, int *nb_find);
int		begin_search(char **file_str, char *pattern_str, int *nb_find);

//wildcards_utils.c
int		replacing_wildcards(t_token *token, int index, t_list *mfl);
void	build_list_all_dir(t_list **list);
t_list	*matching_file(char **f_name, char **patterns, int nb_pat, char *str);
t_list	*build_mf_lst(t_list *list, char **patterns, char *str);
t_list	*build_list_dir(t_list *list);

#endif
