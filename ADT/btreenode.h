#ifndef __BTREENODE_H
#define __BTREENODE_H

#include <stdbool.h>

struct BTreeNode
{
    int degree;
    int *keys;
    struct BTreeNode **childNodes;
    int currNumKeys;
    bool isLeaf;
} bTreeNode;

struct BTreeNode *newBTreeNode(int degree, bool leaf)
{
    struct BTreeNode *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    newNode->degree = degree;
    newNode->isLeaf = leaf;
    newNode->keys = malloc(sizeof(degree - 1));
    newNode->childNodes = malloc((degree) * sizeof(struct BTreeNode));

    return newNode;
}

#endif