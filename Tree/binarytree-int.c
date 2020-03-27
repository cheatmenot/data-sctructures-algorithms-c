#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../ADT/binarytreenode.h"

void newRootNode(struct BinaryTreeNode **root_pointer, int elem)
{
    struct BinaryTreeNode *new_node = newNode(elem);

    *root_pointer = new_node;
}

void newLeftNode(struct BinaryTreeNode **root_pointer, struct BinaryTreeNode *parent_pointer, int elem)
{
    struct BinaryTreeNode *new_node = newNode(elem);
    new_node->parent = parent_pointer;

    if (parent_pointer->left != NULL)
    {
        printf("//replacing left element %d with %d\n", parent_pointer->left->elem, elem);
        struct BinaryTreeNode *del_node = parent_pointer->left;
        free(del_node);
    }

    parent_pointer->left = new_node;
}

void newRightNode(struct BinaryTreeNode **root_pointer, struct BinaryTreeNode *parent_pointer, int elem)
{
    struct BinaryTreeNode *new_node = newNode(elem);
    new_node->parent = parent_pointer;

    if (parent_pointer->right != NULL)
    {
        printf("//replacing right element %d with %d\n", parent_pointer->right->elem, elem);
        struct BinaryTreeNode *del_node = parent_pointer->right;
        free(del_node);
    }

    parent_pointer->right = new_node;
}

void preOrderBinaryTraversal(struct BinaryTreeNode *start_pointer)
{
    printf("%d ", start_pointer->elem);
    if (start_pointer->left != NULL)
        preOrderBinaryTraversal(start_pointer->left);
    if (start_pointer->right != NULL)
        preOrderBinaryTraversal(start_pointer->right);
}

void postOrderBinaryTraversal(struct BinaryTreeNode *start_pointer)
{
    if (start_pointer->left != NULL)
        postOrderBinaryTraversal(start_pointer->left);
    if (start_pointer->right != NULL)
        postOrderBinaryTraversal(start_pointer->right);
    printf("%d ", start_pointer->elem);
}

void inOrderBinaryTraversal(struct BinaryTreeNode *start_pointer)
{
    if (start_pointer->left != NULL)
        inOrderBinaryTraversal(start_pointer->left);
    printf("%d ", start_pointer->elem);
    if (start_pointer->right != NULL)
        inOrderBinaryTraversal(start_pointer->right);
}

void removeExternalNode(struct BinaryTreeNode *external_node_pointer)
{
    if (external_node_pointer->left == NULL && external_node_pointer->right == NULL)
    {
        if (external_node_pointer == external_node_pointer->parent->left)
        {
            external_node_pointer->parent->left = NULL;
            struct BinaryTreeNode *del_node = external_node_pointer->left;
            free(del_node);
        }
        else if (external_node_pointer == external_node_pointer->parent->right)
        {
            external_node_pointer->parent->right = NULL;
            struct BinaryTreeNode *del_node = external_node_pointer->right;
            free(del_node);
        }
        else
        {
            struct BinaryTreeNode *del_node = external_node_pointer->right;
            free(del_node);
        }
    }
    else
    {
        printf("this node %d is not an external node!\n", external_node_pointer->elem);
    }
}

void removeNodeUsingPostOrderTraversal(struct BinaryTreeNode *internal_node_pointer)
{
    if (internal_node_pointer->left != NULL)
        removeNodeUsingPostOrderTraversal(internal_node_pointer->left);
    if (internal_node_pointer->right != NULL)
        removeNodeUsingPostOrderTraversal(internal_node_pointer->right);
    struct BinaryTreeNode *del_node = internal_node_pointer;
    free(del_node);
}

void removeNode(struct BinaryTreeNode **root_pointer, struct BinaryTreeNode *node_pointer)
{
    if (node_pointer == *root_pointer)
    {
        removeNodeUsingPostOrderTraversal(node_pointer);
        *root_pointer = NULL;
    }
    else if (node_pointer == node_pointer->parent->left)
    {
        node_pointer->parent->left = NULL;
        removeNodeUsingPostOrderTraversal(node_pointer);
    }
    else if (node_pointer == node_pointer->parent->right)
    {
        node_pointer->parent->right = NULL;
        removeNodeUsingPostOrderTraversal(node_pointer);
    }
}

int main()
{
    struct BinaryTreeNode *binary_tree = NULL;
    printTreeFromRootToLeaf(binary_tree);
    printf("//newRootNode(5)\n");
    newRootNode(&binary_tree, 5);
    printTreeFromRootToLeaf(binary_tree);
    printf("//Height is %d\n", height(binary_tree));
    printf("//newLeftNode(4)\n");
    newLeftNode(&binary_tree, binary_tree, 4);
    printTreeFromRootToLeaf(binary_tree);
    printf("//replace newLeftNode(7)\n");
    newLeftNode(&binary_tree, binary_tree, 7);
    printTreeFromRootToLeaf(binary_tree);
    printf("//newRightNode(1)\n");
    newRightNode(&binary_tree, binary_tree, 1);
    printTreeFromRootToLeaf(binary_tree);
    printf("//replace newRightNode(9)\n");
    newRightNode(&binary_tree, binary_tree, 9);
    printTreeFromRootToLeaf(binary_tree);
    printf("//adding newLeftNode(1), newRightNode(2) on node with element 7\n");
    newLeftNode(&binary_tree, binary_tree->left, 1);
    newRightNode(&binary_tree, binary_tree->left, 2);
    printTreeFromRootToLeaf(binary_tree);
    printf("//adding newRightNode(3) on elem 9, newRightNode(4) on element 3\n");
    newRightNode(&binary_tree, binary_tree->right, 3);
    newRightNode(&binary_tree, binary_tree->right->right, 4);
    printTreeFromRootToLeaf(binary_tree);
    printf("//adding newLeftNode(6) on elem 9\n");
    newLeftNode(&binary_tree, binary_tree->right, 6);
    printTreeFromRootToLeaf(binary_tree);
    printf("//removing external node with elemet 6\n");
    removeExternalNode(binary_tree->right->left);
    printTreeFromRootToLeaf(binary_tree);
    printf("//removeExternalNode(7) which is not allowed using this removed function\n");
    removeExternalNode(binary_tree->left);
    printf("//preOrderBinaryTraversal on root\n");
    preOrderBinaryTraversal(binary_tree);
    printf("\n//preOrderBinaryTraversal on left subtree\n");
    preOrderBinaryTraversal(binary_tree->left);
    printf("\n//preOrderBinaryTraversal on right subtree\n");
    preOrderBinaryTraversal(binary_tree->right);
    printf("\n//postOrderBinaryTraversal on root\n");
    postOrderBinaryTraversal(binary_tree);
    printf("\n//inOrderBinaryTraversal on root\n");
    inOrderBinaryTraversal(binary_tree);
    printf("\n//Print Befor Removing\n");
    printTreeFromRootToLeaf(binary_tree);
    printf("//Height is %d\n", height(binary_tree));
    printf("//removeNode left subtree\n");
    removeNode(&binary_tree, binary_tree->left);
    printTreeFromRootToLeaf(binary_tree);
    printf("//removeNode right subtree right value\n");
    removeNode(&binary_tree, binary_tree->right->right);
    printTreeFromRootToLeaf(binary_tree);
    printf("//removeNode right subtree\n");
    removeNode(&binary_tree, binary_tree->right);
    printTreeFromRootToLeaf(binary_tree);
    printf("//add left and right node\n");
    newLeftNode(&binary_tree, binary_tree, 0);
    newRightNode(&binary_tree, binary_tree, 8);
    printTreeFromRootToLeaf(binary_tree);
    printf("//removeNode root\n");
    removeNode(&binary_tree, binary_tree);
    printTreeFromRootToLeaf(binary_tree);
}
