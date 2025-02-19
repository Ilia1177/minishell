/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:56:47 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/19 17:58:24 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/****************************************/
/*               BUILTINS               */
/****************************************/
// Builtin_utils
int			exist(char **envp, char *name);
int			catch_name(char **buff, char *str);
char		*catch_value(char *str);
int			print_working_dir(t_bintree *node, t_data *data);
int			print_env(t_bintree *node, char **envp, char *format);
//change_dir.c
int			change_dir(t_bintree *node, t_data *data);
//echo.c
int			echo(t_bintree *node, t_data *data);
//exit.c
int			exit_minishell(t_bintree *node, t_data *data);
//export.c
int			update_envp(t_data *data, char *str);
int			export(t_bintree *node, t_data *data);
char		**set_env(char *name, char *value, char **old_envp);

//unset.c
int			unset(t_bintree *node, t_data *data);

#endif
