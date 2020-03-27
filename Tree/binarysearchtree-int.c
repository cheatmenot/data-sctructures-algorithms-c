#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../ADT/binarytreenode.h"

struct BinaryTreeNode *searcher(struct BinaryTreeNode *node, int elem)
{
    if (node == NULL || node->elem == elem)
    {
        return node;
    }
    else if (node->elem < elem)
    {
        return searcher(node->right, elem);
    }
    else if (node->elem > elem)
    {
        return searcher(node->left, elem);
    }
}

void search(struct BinaryTreeNode *node, int elem)
{
    if (node == NULL)
    {
        printf("Binary Tree is empty during search!\n");
    }
    else
    {
        struct BinaryTreeNode *search_node = searcher(node, elem);
        if (search_node == NULL)
        {
            printf("Cannot find element -> %d!\n", elem);
        }
        else
        {
            printf("Found element -> %d!\n", elem);
        }
    }
}

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

void insertNode(struct BinaryTreeNode **root_pointer, int elem)
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

struct BinaryTreeNode *deleter(struct BinaryTreeNode *node, int elem)
{
    if (node == NULL)
        return node;

    if (elem < node->elem)
        node->left = deleter(node->left, elem);

    else if (elem > node->elem)
        node->right = deleter(node->right, elem);

    else
    {
        if (node->left == NULL)
        {
            struct BinaryTreeNode *temp_node = node->right;
            free(node);
            return temp_node;
        }
        else if (node->right == NULL)
        {
            struct BinaryTreeNode *temp_node = node->left;
            free(node);
            return temp_node;
        }

        struct BinaryTreeNode *succesor_node = node->right;
        while (succesor_node && succesor_node->left != NULL)
        {
            succesor_node = succesor_node->left;
        }

        node->elem = succesor_node->elem;

        node->right = deleter(node->right, succesor_node->elem);
    }
    return node;
}

void deleteNode(struct BinaryTreeNode **root_pointer, int elem)
{
    struct BinaryTreeNode *root_node = *root_pointer;
    if (root_node == NULL)
    {
        printf("Binary Search is empty during delete!\n");
    }
    else if (root_node->elem == elem)
    {
        struct BinaryTreeNode *new_node = deleter(*root_pointer, elem);
        *root_pointer = new_node;
    }
    else
    {
        deleter(*root_pointer, elem);
    }
}

int main()
{
    struct BinaryTreeNode *binary_search_tree = NULL;
    printTreeFromRootToLeaf(binary_search_tree);
    deleteNode(&binary_search_tree, 7);
    search(binary_search_tree, 7);
    printf("//insert node 5, 8, 3\n");
    insertNode(&binary_search_tree, 5);
    insertNode(&binary_search_tree, 8);
    insertNode(&binary_search_tree, 3);
    printTreeFromRootToLeaf(binary_search_tree);
    printf("//trying to delete and search non-existing element 7\n");
    deleteNode(&binary_search_tree, 7);
    search(binary_search_tree, 7);
    printTreeFromRootToLeaf(binary_search_tree);
    printf("//search and delete element 5, 8, 3\n");
    search(binary_search_tree, 5);
    search(binary_search_tree, 8);
    search(binary_search_tree, 3);
    deleteNode(&binary_search_tree, 5);
    deleteNode(&binary_search_tree, 8);
    deleteNode(&binary_search_tree, 3);
    printTreeFromRootToLeaf(binary_search_tree);
    printf("//insert node 5, 8, 3, 2, 4, 7, 9\n");
    insertNode(&binary_search_tree, 5);
    insertNode(&binary_search_tree, 8);
    insertNode(&binary_search_tree, 3);
    insertNode(&binary_search_tree, 2);
    insertNode(&binary_search_tree, 4);
    insertNode(&binary_search_tree, 7);
    insertNode(&binary_search_tree, 9);
    printTreeFromRootToLeaf(binary_search_tree);
    printf("//delete element 2\n");
    deleteNode(&binary_search_tree, 2);
    printTreeFromRootToLeaf(binary_search_tree);
    printf("//delete element 2\n");
    deleteNode(&binary_search_tree, 5);
    printTreeFromRootToLeaf(binary_search_tree);
}
