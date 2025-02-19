/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:53:18 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/19 19:21:10 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/****************************************/
/*                EXEC                  */
/****************************************/
//exec.c 
int			exec_cmd(t_bintree *node, t_data *data);

//exec_utils.c
char		**get_paths(char **env);
char		*get_full_path(char **paths, char *str);
int			build_cmd(t_bintree *node, t_data *data);
char		**tab_dup(char **tab);
t_cmd		*cmddup(t_cmd *cmd);
int			update_envp(t_data *data, char *str);

//exec_utils_supp.c
int			redir(t_bintree *node);
char		**get_paths(char **env);
int			is_directory(char *path);

//exec_tree.c
int			execute_tree(t_data *data);
int			connect_node(t_bintree *a, t_bintree *b);
int			execute_node(t_bintree *node, t_data *data);

#endif
