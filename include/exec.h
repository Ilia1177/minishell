/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:53:18 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/26 20:03:06 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/****************************************/
/*                EXEC                  */
/****************************************/
//exec.c 
int			exec_cmd(t_bintree *node, t_data *data);
void		connect_stdio(t_bintree *a, t_bintree *b);

//exec_utils.c
char		**get_paths(char **env);
char		*get_full_path(char **paths, char *str);
int			build_cmd(t_bintree *node, t_data *data);
int			update_envp(t_data *data, char *str);

//exec_utils_supp.c
int			redir(t_bintree *node);
char		**get_paths(char **env);
int			is_directory(char *path);

//exec_tree.c
int			execute_tree(t_data *data);
int			execute_node(t_bintree *node, t_data *data);
int			connect_node(t_bintree *a, t_bintree *b);
int			get_child_status(t_data *data);

//exec_utils_supp2.c
t_cmd		*cmddup(t_cmd *cmd);
char		**tab_dup(char **tab);
int			find_cmd_in_paths(char *str, t_bintree *node, t_data *data);

#endif
