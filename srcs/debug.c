#include "minishell.h"

void print_tree(t_bintree *tree, int space)
{
    if (tree == NULL)
        return;

    // Increase distance between levels
    int spacing = 5;
    space += spacing;

    // Print the right subtree first
    print_tree(tree->right, space);

    // Print the current node with indentation
    printf("\n");
    for (int i = spacing; i < space; i++)
        printf(" ");
    printf("(%s)\n", tree->input);
    // Print the left subtree
    print_tree(tree->left, space);
}

void	print_rdir(t_token *token)
{
	int	i;

	i = 0;
	ft_printf(2, "token %s redir :", token->input);
	while (token->cmd->rdir[i].name)
	{
		ft_printf(2, "name ='%s' type ='%d'\n", token->cmd->rdir[i].name, token->cmd->rdir[i].type);
		i++;
	}
	ft_printf(2,"\n");
}

void	print_list(t_token *list)
{
	int	i;

	i = 0;
	while(list)
	{
		printf("TOKEN nº%d : input = %6s, type = %d", i++, list->input, list->type);
		if (list->type == CMD)
		{
			printf (", args = ");
			print_args(list->cmd->args);
			printf ("\n");
		}
		else
			printf("\n");
		/* printf("in_rdir = %6s, out_rdir = %6s, append = %6s, heredoc = %6s\n\n", list->cmd->in_rdir, list->cmd->out_rdir, list->cmd->append, list->cmd->heredoc); */
		list = list->next;
	}
}

// print **arguments for DEBUG
void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("'%s', ", args[i]);
		i++;
	}
}
