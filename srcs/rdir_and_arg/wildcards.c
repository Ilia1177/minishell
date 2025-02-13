/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:06:48 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/13 18:03:46 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	wildcards(t_token *token, t_data *data)
{
  DIR* dir;
  struct dirent* dr;
  char  *str;
  char **patterns;
  char  *tofind;
  char  **args;
  int   pos_wild;
  int nb_pat;
  int i;
  int nb_find;
  int   arg_len;

  (void)data;
  (void)tofind;
  (void)i; 
  if (!token->cmd->args[1] || !ft_strchr(token->cmd->args[1],'*'))
    return ;

  
  args = token->cmd->args;
  str = args[1];
  arg_len = ft_strlen(str);
  
  if (ft_strcmp(str, "*.")== 0 || ft_strcmp(str, ".*")== 0 )
    printf(NMF_MSG);
 
  
  pos_wild = ft_strnlen(str, '*');
  printf("pos *:%d\n",pos_wild);

  patterns = ft_split(str,'*');

  nb_pat=0;
  while (patterns[nb_pat])
    nb_pat++;
  printf("nb patterns *:%d\n",nb_pat);
  
  dir = opendir(".");
  
  if (!dir)
  {
    perror("opendir");
    exit(EXIT_FAILURE);
  }

  
  while ((dr = readdir(dir)))
  {
    i = 0;
    nb_find = 0;
    tofind = dr->d_name;
    //teste commence par aaaa*
    /* if (!ft_strncmp(dr->d_name, str, pos_wild)) */
    while (patterns[i])
    {
      if ( i == 0 && str[i] != '*')
      {
        if (!ft_strncmp(tofind, patterns[i], ft_strlen(patterns[i])))
        {
          tofind = ft_substr(tofind,ft_strlen(patterns[i]), ft_strlen(tofind));
          ft_printf(1,"%s\n", tofind);
          nb_find++;
        }
        else
          break ;
      }
      else if (i == nb_pat -1 && str[arg_len-1] != '*')
      {
        tofind = ft_substr(tofind,ft_strlen(tofind)-ft_strlen(patterns[i]), ft_strlen(tofind));
        if (tofind)
        {
          if (!ft_strcmp(tofind, patterns[i]))
          {
            ft_printf(1,"end -%s\n", tofind);
            nb_find++;
          }
          else
            break ;
        }
      }
      else
      {
        tofind = ft_strnstr(tofind, patterns[i], ft_strlen(tofind));
        if (tofind)
        {
          tofind = ft_substr(tofind, 1, ft_strlen(tofind));
          ft_printf(1,"%s\n", tofind );
          nb_find++;
        }
        else
          break ;
      }
      if (nb_find == nb_pat)
        ft_printf(1,"TROUVE YOUPI---%s\n", dr->d_name );

      i++;
    }
  }
  
  closedir(dir);
}
