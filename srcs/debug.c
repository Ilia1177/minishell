#include "minishell.h"

void	print_tree(t_bintree *root)
{
	if (!root)
		return ;
	if (root->left)
		print_tree(root->left);
	if (root->right)
		print_tree(root->right);
	if (root->content)
	{
		args_print(root->content);
		printf("\n");
	}
}

// print **arguments for DEBUG
void	args_print(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("%s ", args[i]);
		i++;
	}
}

