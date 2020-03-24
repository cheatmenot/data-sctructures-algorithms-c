#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../ADT/binarytreenode.h"

struct BinaryTreeNode *inserter(struct BinaryTreeNode *node, struct BinaryTreeNode *parent, int elem)
{
    if (node == NULL)
    {
        struct BinaryTreeNode *new_node = newNode(elem);
        new_node->parent = parent;
        node = new_node;
    }
    if (node->elem > elem)
    {
        node->left = inserter(node->left, node, elem);
    }
    else if (node->elem < elem)
    {
        node->right = inserter(node->right, node, elem);
    }
    return node;
}

void insert(struct BinaryTreeNode **root_pointer, int elem)
{
    if (*root_pointer == NULL)
    {
        struct BinaryTreeNode *new_node = newNode(elem);
        *root_pointer = new_node;
    }
    else
    {
        inserter(*root_pointer, *root_pointer, elem);
    }
}

int main()
{
    struct BinaryTreeNode *binary_search_tree = NULL;
    printTreeFromRootToLeaf(binary_search_tree);
    insert(&binary_search_tree, 5);
    insert(&binary_search_tree, 6);
    insert(&binary_search_tree, 4);
    printTreeFromRootToLeaf(binary_search_tree);
}
