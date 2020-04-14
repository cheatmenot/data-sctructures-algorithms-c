#ifndef __BINARYTREENODE_H
#define __BINARYTREENODE_H

struct BinaryTreeNode
{
    int elem;
    struct BinaryTreeNode *parent;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} binaryTreeNode;

struct BinaryTreeNode *newNode(int elem)
{
    struct BinaryTreeNode *new_node = (struct BinaryTreeNode *)malloc(sizeof(struct BinaryTreeNode));
    new_node->elem = elem;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

void printArray(int ints[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (i == (size - 1))
            printf("%d", ints[i]);
        else
            printf("%d->", ints[i]);
    }
    printf("\n");
}

void printTreeRecursion(struct BinaryTreeNode *node, int path[], int pathLen)
{
    if (node == NULL)
        return;

    path[pathLen] = node->elem;
    pathLen++;

    if (node->left == NULL && node->right == NULL)
    {
        printArray(path, pathLen);
    }
    else
    {
        printTreeRecursion(node->left, path, pathLen);
        printTreeRecursion(node->right, path, pathLen);
    }
}

void printTreeFromRootToLeaf(struct BinaryTreeNode *node)
{
    if (node != NULL)
    {
        int path[1000];
        printTreeRecursion(node, path, 0);
    }
    else
    {
        printf("This Binary Tree is Empty!\n");
    }
}

int height(struct BinaryTreeNode *root_node)
{
    if (root_node == NULL)
        return 0;
    else
    {
        int leftHeight = height(root_node->left);
        int rightHeight = height(root_node->right);

        if (leftHeight > rightHeight)
            return leftHeight + 1;
        else
            return rightHeight + 1;
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

#endif