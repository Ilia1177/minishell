/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-jm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:19:01 by npolack           #+#    #+#             */
/*   Updated: 2025/01/28 13:51:48 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get user prompt
char	*listen_to_user(char *prompt)
{
	char	*input;

	input = readline(prompt);
	if (!input)
		return (NULL);
	add_history(input);
	return (input);
}

void	init_shell(t_data *data)
{
	rl_catch_signals = 0; // Disable readline's signal handling
	signal_caught = 0;
	data->tree = NULL;
	data->token_list = NULL;
	data->paths = NULL;
	data->user_input = NULL;
}

int	run_shell(t_data *data)
{
	//t_token		*cpy;
	char		wd[1024];
	char		*tmp;


	while (1)
	{
		if (getcwd(wd, sizeof(wd)))
		{
			tmp = ft_strjoin("M!N!$H3LL>", wd);
			data->prompt = ft_strjoin(tmp, ">$");
			free(tmp);
		}
		data->user_input = listen_to_user(data->prompt);
	//	syntax_error(data->user_input);
		if (!data->user_input || !ft_strcmp(data->user_input, ""))	// doesnt work either...
		{
			free(data->user_input);
			/* if (ft_strnstr(data->user_input,"<<", ft_strlen(data->user_input))) */
			/* 	get_here_doc("end"); */
			free(data->prompt);
			ft_putendl_fd("exit", 2);
			exit(0);
		}
		//printf("\n\n----------- List of token is : -");
		data->token_list = tokenize(data->user_input);
		//printf( "nb_word -> :%d\n", ft_nbword(data->user_input) );

		print_list(data->token_list);
		//printf("\n\n----------- DEBUG TREE ---------");
		//cpy = data->token_list;
		//data->tree = build_tree(&cpy, CMD);
		//print_tree(data->tree, 0); // print the tree for debug
		//printf("\n\n----------- EXECUTION ----------");
		//execute_tree(data); 
		//free_minishell(data);
		init_shell(data);
	}
}

int	main(int ac, char **argv, char **envp)
{
	t_data				data;

	(void)argv;
	if (ac > 1)
		printf("minishell: ???\n");
	register_signals();
	data.envp = envp;
	init_shell(&data);
	run_shell(&data);
	//free_minishell(&data);
	return (signal_caught);
}
