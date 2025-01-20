#include "minishell.h"

void	print_tree(t_bintree *root)
{
	if (!root)
		return ;
	if (root->left)
		print_tree(root->left);
	if (root->content)
	{
		printf("%s ", root->content[0]);
		//print_args(root->content);
	}
	if (root->right)
		print_tree(root->right);

}

void	print_list(t_token *list)
{
	printf("list = ");
	while(list)
	{
		printf("input = %s, type = %d\n", list->input, list->type);
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
		printf("%s ", args[i]);
		i++;
	}
}
