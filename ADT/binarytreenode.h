#ifndef __BINARYTREENODE_H
#define __BINARYTREENODE_H

struct BinaryTreeNode
{
    int elem;
    struct BinaryTreeNode *parent;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} binaryTreeNode;

#endif