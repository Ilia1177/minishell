#include "minishell.h"

void	print_tree(t_bintree *root)
{
	printf("tree = ");
	if (!root)
		return ;
	if (root->left)
		print_tree(root->left);
	if (root->right)
		print_tree(root->right);
	if (root->content)
	{
		print_args(root->content);
		printf("\n");
	}
}

void	print_list(t_token *list)
{
	printf("list = ");
	while (list)
	{
		print_args(list->content);
		list = list->next;
	}
	printf("\n");
}
// print **arguments for DEBUG
void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("%s ", args[i]);
		i++;
	}
}

