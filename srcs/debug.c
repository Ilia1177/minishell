#include "minishell.h"

/*void	print_tree(t_bintree *root)
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

}*/

void print_tree(t_bintree *tree, int space) {
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
