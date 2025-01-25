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
    printf("(%s)\n", tree->content[0]);
    // Print the left subtree
    print_tree(tree->left, space);
}

void	print_list(t_token *list)
{
	int	i;

	i = 0;
	printf("list = \n");
	while(list)
	{
		printf("input %d = %6s, type = %d", i++, list->input, list->type);
		if (list->type == CMD)
		{
			printf (", args = ");
			print_args(list->cmd->args);
			printf ("\n");
		}
		else
			printf("\n");
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
		printf("\t%4s, ", args[i]);
		i++;
	}
}
