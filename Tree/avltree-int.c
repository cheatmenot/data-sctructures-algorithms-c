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

//   b               d
//  / \      <-     / \
// a   d     ->    b   e
//    /  \        / \
//   c    e      a   c
struct BinaryTreeNode *rotateLeft(struct BinaryTreeNode *b)
{
    struct BinaryTreeNode *d = b->right;
    if (d->left != NULL)
    {
        struct BinaryTreeNode *c = d->left;
        b->right = c;
        c->parent = b;
        d->left = b;
        b->parent = d;
    }
    else
    {
        d->left = b;
        b->right = NULL;
        b->parent = d;
    }

    return d;
}

struct BinaryTreeNode *rotateRight(struct BinaryTreeNode *d)
{
    struct BinaryTreeNode *b = d->left;
    if (b->right != NULL)
    {
        struct BinaryTreeNode *c = b->right;
        d->left = c;
        c->parent = d;
        b->right = d;
        d->parent = b;
    }
    else
    {
        b->right = d;
        d->left = NULL;
        d->parent = b;
    }

    return b;
}

int getBalance(struct BinaryTreeNode *node)
{
    return (node == NULL) ? 0 : (height(node->left) - height(node->right));
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

    int balance = getBalance(node);

    if (balance > 1 && elem < node->left->elem)
    {
        printf("Left Left Case: %d, %d, %d\n", elem, node->elem, node->left->elem);
        return rotateRight(node);
    }
    else if (balance < -1 && elem > node->right->elem)
    {
        printf("Right Right Case: %d, %d\n", elem, node->right->elem);
        return rotateLeft(node);
    }
    else if (balance > 1 && elem > node->left->elem)
    {
        printf("Left Right Case: %d, %d\n", elem, node->left->elem);
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    else if (balance < -1 && elem < node->right->elem)
    {
        printf("Right Left Case: %d, %d\n", elem, node->right->elem);
        node->right = rotateRight(node->right);
        return rotateLeft(node);
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
        *root_pointer = inserter(*root_pointer, *root_pointer, elem);
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

    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0)
    {
        printf("Left Left Case: %d, %d\n", balance, getBalance(node->left));
        return rotateRight(node);
    }
    else if (balance > 1 && getBalance(node->left) < 0)
    {
        printf("Left Right Case: %d, %d\n", balance, getBalance(node->left));
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    else if (balance < -1 && getBalance(node->right) <= 0)
    {
        printf("Right Right Case: %d, %d\n", balance, getBalance(node->right));
        return rotateLeft(node);
    }
    if (balance < -1 && getBalance(node->right) > 0)
    {
        printf("Right Left Case: %d, %d\n", balance, getBalance(node->right));
        node->right = rotateRight(node->right);
        return rotateLeft(node);
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
    else
    {
        *root_pointer = deleter(*root_pointer, elem);
    }
}

int main()
{
    struct BinaryTreeNode *avl_tree = NULL;
    printf("//AVL TREE 1\n");
    printTreeFromRootToLeaf(avl_tree);
    deleteNode(&avl_tree, 2);
    printf("//insert node 2, 1, 4, 3, 6\n");
    insertNode(&avl_tree, 2);
    insertNode(&avl_tree, 1);
    insertNode(&avl_tree, 4);
    insertNode(&avl_tree, 3);
    insertNode(&avl_tree, 6);
    search(avl_tree, 7);
    search(avl_tree, 6);
    search(avl_tree, 2);
    printTreeFromRootToLeaf(avl_tree);
    printf("//rotateLeft\n");
    avl_tree = rotateLeft(avl_tree);
    printTreeFromRootToLeaf(avl_tree);
    printf("//rotateRight\n");
    avl_tree = rotateRight(avl_tree);
    printTreeFromRootToLeaf(avl_tree);
    printf("//deleteNode 1\n");
    deleteNode(&avl_tree, 1);
    printTreeFromRootToLeaf(avl_tree);
    printf("//deleteNode 6\n");
    deleteNode(&avl_tree, 6);
    printTreeFromRootToLeaf(avl_tree);

    struct BinaryTreeNode *avl_tree2 = NULL;
    printf("\n//AVL TREE 2\n");
    printf("//insert node 13, 10, 15, 5, 11, 16, 4, 6 \n");
    insertNode(&avl_tree2, 13);
    insertNode(&avl_tree2, 10);
    insertNode(&avl_tree2, 15);
    insertNode(&avl_tree2, 5);
    insertNode(&avl_tree2, 11);
    insertNode(&avl_tree2, 16);
    insertNode(&avl_tree2, 4);
    insertNode(&avl_tree2, 6);
    printTreeFromRootToLeaf(avl_tree2);
    printf("//insert node 14 \n");
    insertNode(&avl_tree2, 14);
    printTreeFromRootToLeaf(avl_tree2);
    printf("//insert node 7, must rotateLeft at 5 and rotateRight at 6\n");
    insertNode(&avl_tree2, 7);
    printTreeFromRootToLeaf(avl_tree2);
    printf("//insert node 3, must rotateRight at 5\n");
    insertNode(&avl_tree2, 3);
    printTreeFromRootToLeaf(avl_tree2);

    struct BinaryTreeNode *avl_tree3 = NULL;
    printf("\n//AVL TREE 3\n");
    printf("//insert node 5, 2, 7, 1, 4, 6, 9, 3, 16\n");
    insertNode(&avl_tree3, 5);
    insertNode(&avl_tree3, 2);
    insertNode(&avl_tree3, 7);
    insertNode(&avl_tree3, 1);
    insertNode(&avl_tree3, 4);
    insertNode(&avl_tree3, 6);
    insertNode(&avl_tree3, 9);
    insertNode(&avl_tree3, 3);
    insertNode(&avl_tree3, 16);
    printTreeFromRootToLeaf(avl_tree3);
    printf("//insert node 15, must rotateRight at 16 and rotateLeft at 9\n");
    insertNode(&avl_tree3, 15);
    printTreeFromRootToLeaf(avl_tree3);
    printf("//insert node 18, rotateLeft at 7\n");
    insertNode(&avl_tree3, 18);
    printTreeFromRootToLeaf(avl_tree3);

    struct BinaryTreeNode *avl_tree4 = NULL;
    printTreeFromRootToLeaf(avl_tree4);
    printf("//insert node 2, 1, 4, 3, 6\n");
    insertNode(&avl_tree4, 10);
    insertNode(&avl_tree4, 6);
    insertNode(&avl_tree4, 11);
    insertNode(&avl_tree4, 5);
    insertNode(&avl_tree4, 7);
    insertNode(&avl_tree4, 0);
    insertNode(&avl_tree4, 4);
    insertNode(&avl_tree4, 1);
    printTreeFromRootToLeaf(avl_tree4);
    printf("//deleteNode 11\n");
    deleteNode(&avl_tree4, 7);
    deleteNode(&avl_tree4, 11);
    printTreeFromRootToLeaf(avl_tree4);
}