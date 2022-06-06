#include "astree.h"

void	astree_make_branch(t_ASTreeNode *root, t_ASTreeNode *left_node, t_ASTreeNode *right_node)
{
	root->left = left_node;
	root->right = right_node;
}