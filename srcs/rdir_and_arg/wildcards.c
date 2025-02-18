/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:06:48 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/18 14:13:20 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/****************************************************
 * check if the pattern is present in the filename 
 * update the file name returns from pattern +1
 * returns 1 if the pattern found
 * *************************************************/
int	middle_search(char **file_str, char *pattern_str, int *nb_find)
{
	char	*tmp_str;

	tmp_str = ft_strnstr(*file_str, pattern_str, ft_strlen(*file_str));
	if (tmp_str)
	{
		tmp_str = ft_substr(tmp_str, 1, ft_strlen(tmp_str));
		free(*file_str);
		*file_str = tmp_str;
		free(tmp_str);
		/* ft_printf(1, "%s\n", *file_str); */
		*nb_find += 1;
		return (1);
	}
	free(tmp_str);
	return (0);
}

/****************************************************
 * check if the file name ending by the pattern
 * after the last wildcards *
 * update the file name after substr -> after pattern
 * returns 1 if the pattern found
 * *************************************************/
int	end_search(char **file_str, char *pattern_str, int *nb_find)
{
	char	*tmp_str;

	tmp_str = ft_substr(*file_str, ft_strlen(*file_str)
			- ft_strlen(pattern_str), ft_strlen(*file_str));
	if (tmp_str && !ft_strcmp(tmp_str, pattern_str))
	{
		free(*file_str);
		*file_str = tmp_str;
		/* ft_printf(1, "%s\n", *file_str); */
		free(tmp_str);
		*nb_find += 1;
		return (1);
	}
	free(tmp_str);
	return (0);
}

/****************************************************
 * check if the file name start by the pattern
 * before the first wildcards *
 * update the file name after substr -> after pattern
 * returns 1 if the pattern found
 * *************************************************/
int	begin_search(char **file_str, char *pattern_str, int *nb_find)
{
	char	*tmp_str;

	if (!ft_strncmp(*file_str, pattern_str, ft_strlen(pattern_str)))
	{
		tmp_str = ft_substr(*file_str, ft_strlen(pattern_str),
				ft_strlen(*file_str));
		free(*file_str);
		*file_str = tmp_str;
		free(tmp_str);
		/* ft_printf(1, "%s\n", *file_str); */
		*nb_find += 1;
		return (1);
	}
	return (0);
}


/****************************************************
 * Sort the current directory list
 * before the first wildcards *
 * update the file name after substr -> after pattern
 * returns 1 if the pattern found
 * *************************************************/
void	sort_list_dir(t_list **list)
{
	t_list	*current;
	t_list	*next;
	char		*curr_str;
	char		*next_str;

	current = *list;
	while(current)
	{
		next = current->next;
		while(next)
		{
			curr_str = (char *)current->content;
			next_str = (char *)next->content;
			if (next && ft_strlowercmp(curr_str, next_str) > 0)
			{
				curr_str = (char *)current->content;
				current->content = next->content;
				next->content = curr_str;
			}
			next = next->next;
		}
		current = current->next;
	}
}

void	print_lst_dir(t_list *list)
{
	t_list	*current;

	current = list;
	printf("print list dir:");
	while (current)
	{
		printf("%s|", (char *)current->content);
		current = current->next;
	}
	printf("\n");
}

/****************************************************
 * build a list of all filename in current directory
 * *************************************************/
void	build_list_all_dir(t_list **list)
{
	t_list			*elem;
	DIR				*dir;
	struct dirent	*dr;
	char			*file_name;

	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}
	while ((dr = readdir(dir)))
	{
		file_name = ft_strdup(dr->d_name);
		//printf("---fichier:%s-type:%d", dr->d_name, dr->d_type);
		elem = ft_lstnew((void *)file_name);
		ft_lstadd_back(list, elem);
	}
	closedir(dir);
	/* print_lst_dir(*list); */
	sort_list_dir(list);
	/* print_lst_dir(*list); */
}

int	only_wild(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str != '*')
			return (0);
		str++;
	}
	return (1);
}
/****************************************************
 * return the file name matching the wildcards pattens
 * elem of matching files list
 * *************************************************/
t_list *matching_file(char *file_name, char **patterns, int nb_pat, char *str)
{
	int i;
	int not_find;
	int nb_find;
	char *tmp_name;
	t_list *elem;
	/**/
	elem = NULL;
 	i = 0;
 	not_find = 1;
 	nb_find = 0;
 	tmp_name = ft_strdup(file_name);
	while (patterns[i] && not_find)
	{
		if (i == 0 && str[i] != '*')
			not_find = begin_search(&file_name, patterns[i], &nb_find);
		else if (i == nb_pat - 1 && str[ft_strlen(str) - 1] != '*')
			not_find = end_search(&file_name, patterns[i], &nb_find);
		else
			not_find = middle_search(&file_name, patterns[i], &nb_find);
		if (nb_find == nb_pat)
		{
			/* ft_printf(1, "TROUVE YOUPI---%s\n", tmp_name); */
			elem = ft_lstnew((void *)tmp_name);
		}
		i++;
	}
	if (!not_find)
		free(tmp_name);
	return (elem);
}

/****************************************************
 * build the list of all files in current directory
 * matching the wildcards pattern
 * *************************************************/
t_list	*build_mf_lst(t_list *list, char **patterns/*, t_list **mfl*/, char *str)
{
	char	*file_name;
	t_list	*lst_dir;
	t_list *match_files_lst;
	t_list *elem;
	int nb_pat;

  nb_pat=0;
  while (patterns[nb_pat])
    nb_pat++;

	lst_dir = list;
	match_files_lst = NULL;
	/* match_files_lst = *mfl; */
	while (lst_dir)
	{
		file_name = ft_strdup((char *)lst_dir->content);
		elem = matching_file(file_name, patterns, nb_pat, str);
		if (elem)
			ft_lstadd_back(&match_files_lst, elem);
		else
			free(file_name);
		lst_dir = lst_dir->next;
	}
	/* *mfl = match_files_lst; */
	/* printf("\nliste args****\n"); */
	/* print_lst_dir(match_files_lst); */
	return(match_files_lst);
}
/****************************************************
 * build the list of all files of current directory
 * except hidden files
 * *************************************************/
t_list	*build_list_dir(t_list *list/*, t_list **mfl*/)
{
	char	*file_name;
	t_list	*lst_dir;
	t_list *match_files_lst;
	t_list *elem;

	lst_dir = list;
	match_files_lst = NULL;
	/* match_files_lst = *mfl; */
	while (lst_dir)
	{
		if (*(char *)lst_dir->content != '.')
		{
		file_name = ft_strdup((char *)lst_dir->content);
		elem = ft_lstnew((void *)file_name);
		ft_lstadd_back(&match_files_lst, elem);
		}
		lst_dir = lst_dir->next;
	}
	/* *mfl = match_files_lst; */
	/* printf("\nliste args only****\n"); */
	/* print_lst_dir(match_files_lst); */
	return(match_files_lst);
}


/****************************************************
 * main wildcards function
 * *************************************************/
void	wildcards(t_token *token, t_data *data)
{
	char	**patterns;
	t_list	*list_all_dir;
	t_list *list_dir;
	t_list *match_files_lst;
	int i;

  (void)data;
	match_files_lst = NULL;
  list_all_dir = NULL;
  list_dir = NULL;
  build_list_all_dir(&list_all_dir);
  list_dir = build_list_dir(list_all_dir/*, &list_dir*/);
  //si il n'y a pas de wildcards
  /* if (!token->cmd->args[1] || !ft_strchr(token->cmd->args[1],'*') */
  /* 	|| !ft_strcmp(token->cmd->args[1], "*.")) */
  /*   return ; */


	i = 0;
	while (token->cmd->args[++i])
	{
		/* match_files_lst = NULL; */
  		if (!token->cmd->args[i] || !ft_strchr(token->cmd->args[i],'*')
  			|| !ft_strcmp(token->cmd->args[i], "*."))
  			continue ;
		else if (only_wild(token->cmd->args[i]))
		{
			/* printf("QUE DES WILDCARDS\n"); */
			match_files_lst = build_list_dir(list_all_dir);
		}
		else
		{
			patterns = ft_split(token->cmd->args[i],'*');
			if (token->cmd->args[i][0] == '.')
				match_files_lst = build_mf_lst(list_all_dir, patterns, token->cmd->args[i]);
			else
				match_files_lst = build_mf_lst(list_dir, patterns, token->cmd->args[i]);
		}
		/* print_lst_dir(match_files_lst); */
		if (match_files_lst)
		{
			/* printf("-avant -replace ARG[%d]:%s\n", i, token->cmd->args[i]); */
			i += replacing_wildcards(token, i, match_files_lst);
			/* printf("-apres -replace n-1 ARG[%d]:%s\n", i-1, token->cmd->args[i-1]); */
			/* printf("-apres -replace ARG[%d]:%s\n", i, token->cmd->args[i]); */
		}
		/* ft_lstclear(&match_files_lst, free); */
		/* i++; */
  }
	/* print_lst_dir(match_files_lst); */
	/* free_tabstr(patterns); */
	/* ft_lstclear(&match_files_lst, free); */
	/* ft_lstclear(&list_dir, free); */
	/* ft_lstclear(&list_all_dir, free); */
	
}
