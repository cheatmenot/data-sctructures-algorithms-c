#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../ADT/btreenode.h"

void printBTree(struct BTreeNode *node)
{
    if (node != NULL)
    {
        int i;
        if (node->isLeaf)
        {
            for (i = 0; i < node->currNumKeys; i++)
            {
                printf("%d, ", node->keys[i]);
            }
        }
        else
        {
            for (i = 0; i < node->currNumKeys; i++)
            {
                printBTree(node->childNodes[i]);
                printf("%d, ", node->keys[i]);
            }
            printBTree(node->childNodes[i]);
        }
    }
}

void splitChild(int childIndex, struct BTreeNode *currentNode, struct BTreeNode *node)
{
    int size = node->degree - 1;
    int middleIndex = currentNode->currNumKeys / 2;
    struct BTreeNode *newNode = newBTreeNode(currentNode->degree, currentNode->isLeaf);

    int j = 0;
    for (int i = middleIndex + 1; i < currentNode->currNumKeys; i++, j++)
    {
        newNode->keys[j] = currentNode->keys[i];
    }
    if (!currentNode->isLeaf)
    {
        for (int i = 0; i < size; i++)
        {
            newNode->childNodes[i] = currentNode->childNodes[i + size];
        }
    }

    currentNode->currNumKeys = middleIndex;

    for (int j = node->currNumKeys; j >= childIndex + 1; j--)
    {
        node->childNodes[j + 1] = node->childNodes[j];
    }

    node->childNodes[childIndex + 1] = newNode;

    for (int j = node->currNumKeys; j > childIndex; j--)
    {
        node->keys[j] = node->keys[j - 1];
        node->childNodes[j] = node->childNodes[j - 1];
    }

    node->keys[childIndex] = currentNode->keys[middleIndex];
    // node->childNodes[childIndex] = node->childNodes;
    node->currNumKeys = node->currNumKeys + 1;
}

void insertNotFull(struct BTreeNode *node, int elem)
{
    int currIndex = node->currNumKeys - 1;
    // printf("insertNotFull %d %d\n", node->currNumKeys, currIndex);
    if (node->isLeaf)
    {
        // printf("insertNotFull if %d %d\n", elem, node->keys[0]);
        while (node->keys[currIndex] > elem)
        {
            node->keys[currIndex + 1] = node->keys[currIndex];
            currIndex--;
        }
        node->keys[currIndex + 1] = elem;
        node->currNumKeys += 1;
    }
    else
    {
        // printf("insertNotFull else %d %d\n", elem, currIndex);
        while (node->keys[currIndex] > elem)
        {
            currIndex--;
        }
        if (node->childNodes[currIndex + 1]->currNumKeys == node->degree - 1)
        {
            // printf("split");
            splitChild(currIndex + 1, node->childNodes[currIndex + 1], node);
            if (node->keys[currIndex + 1] < elem)
            {
                currIndex++;
            }
        }
        // printf("insertNotFull elseExit %d\n", currIndex);
        insertNotFull(node->childNodes[currIndex + 1], elem);
    }
}

void insert2(struct BTreeNode **rootNode, int degree, int elem)
{
    struct BTreeNode *tempNode = *rootNode;
    // printf("mayor2 %d\n", tempNode->childNodes[0]->currNumKeys);
    if (*rootNode == NULL)
    {
        struct BTreeNode *newNode = newBTreeNode(degree, true);
        newNode->keys[0] = elem;
        newNode->currNumKeys = 1;
        *rootNode = newNode;
    }
    else
    {
        // printf("%d %d\n", tempNode->currNumKeys, tempNode->keys[0]);
        // printf("insert else %d\n", tempNode->currNumKeys);
        if (tempNode->currNumKeys == degree - 1)
        {
            int currIndex = tempNode->currNumKeys - 1;
            while (tempNode->keys[currIndex] > elem)
            {
                currIndex--;
            }
            // printf("alona %d\n", tempNode->childNodes[0]->currNumKeys);
            if (tempNode->childNodes[currIndex + 1]->currNumKeys == degree - 1)
            {
                // printf("insert else if\n");
                struct BTreeNode *newRoot = newBTreeNode(tempNode->degree, false);
                newRoot->childNodes[0] = tempNode;
                splitChild(0, tempNode, newRoot);

                int i = 0;
                if (newRoot->keys[0] < elem)
                {
                    i++;
                }
                insertNotFull(newRoot->childNodes[i], elem);
                *rootNode = newRoot;
            }
            else
            {
                // printf("wew %d %d\n", tempNode->childNodes[currIndex + 1]->currNumKeys, degree - 1);
                insertNotFull(tempNode->childNodes[currIndex + 1], elem);
                *rootNode = tempNode;
            }
        }
        else
        {
            insertNotFull(tempNode, elem);
            *rootNode = tempNode;
        }
    }
}

void insert(struct BTreeNode **rootNode, int degree, int elem)
{
    struct BTreeNode *tempNode = *rootNode;
    if (*rootNode == NULL)
    {
        struct BTreeNode *newNode = newBTreeNode(degree, true);
        newNode->keys[0] = elem;
        newNode->currNumKeys = 1;
        *rootNode = newNode;
    }
    else
    {
        // printf("insert else %d %d\n", tempNode->currNumKeys, tempNode->isLeaf);
        // printf("%d %d %d\n", tempNode->currNumKeys, tempNode->keys[0], tempNode->keys[1]);
        if (tempNode->currNumKeys == degree - 1)
        {
            // printf("insert else if\n");
            struct BTreeNode *newRoot = newBTreeNode(tempNode->degree, false);
            newRoot->childNodes[0] = tempNode;
            splitChild(0, tempNode, newRoot);

            int i = 0;
            if (newRoot->keys[0] < elem)
            {
                i++;
            }
            insertNotFull(newRoot->childNodes[i], elem);
            *rootNode = newRoot;
        }
        else
        {
            insertNotFull(tempNode, elem);
            *rootNode = tempNode;
        }
    }
}

void printKeysInANode(struct BTreeNode *node)
{
    if (node != NULL)
    {
        for (int i = 0; i < node->currNumKeys; i++)
        {
            if (i < (node->currNumKeys - 1))
            {
                printf("%d, ", node->keys[i]);
            }
            else if (i == (node->currNumKeys - 1))
            {
                printf("%d", node->keys[i]);
            }
        }
    }
}

struct BTreeNode *searcher(struct BTreeNode *node, int elem)
{
    int i = 0;
    while (i < node->currNumKeys && elem > node->keys[i])
    {
        i++;
    }

    if (node->keys[i] == elem)
    {
        return node;
    }

    if (node->isLeaf)
    {
        return NULL;
    }

    return searcher(node->childNodes[i], elem);
}

void search(struct BTreeNode *node, int elem)
{
    if (node == NULL)
    {
        printf("BTree is NULL, cannot be searched!\n");
    }
    else
    {
        struct BTreeNode *searchRes = searcher(node, elem);
        if (searchRes != NULL)
        {
            printf("Found element %d on BTree\n", elem);
        }
        else
        {
            printf("Element %d does not exist!\n", elem);
        }
    }
}

int findIndex(struct BTreeNode *node, int elem)
{
    int index = 0;
    while (index < node->currNumKeys && node->keys[index] < elem)
    {
        ++index;
    }
    return index;
}

int findPredecessorOfIndex(struct BTreeNode *node, int index)
{
    struct BTreeNode *tempNode = node->childNodes[index];
    while (!tempNode->isLeaf)
    {
        tempNode = tempNode->childNodes[tempNode->currNumKeys];
    }
    return tempNode->keys[tempNode->currNumKeys - 1];
}

int findSuccessorOfIndex(struct BTreeNode *node, int index)
{
    struct BTreeNode *tempNode = node->childNodes[index + 1];
    while (!tempNode->isLeaf)
    {
        tempNode = tempNode->childNodes[0];
    }
    return tempNode->keys[0];
}

void borrowFromPrev(struct BTreeNode *node, int index)
{
    struct BTreeNode *child = node->childNodes[index];
    struct BTreeNode *childNext = node->childNodes[index + 1];

    for (int i = child->currNumKeys - 1; i >= 0; --i)
    {
        child->keys[i + 1] = childNext->keys[i];
    }

    if (!child->isLeaf)
    {
        for (int i = child->currNumKeys; i >= 0; --i)
        {
            child->childNodes[i + node->degree] = childNext->childNodes[i];
        }
    }

    child->keys[0] = node->keys[index - 1];

    if (!child->isLeaf)
    {
        for (int i = child->currNumKeys; i >= 0; --i)
        {
            child->childNodes[i + node->degree] = childNext->childNodes[i];
        }
    }

    node->keys[index - 1] = childNext->keys[childNext->currNumKeys - 1];

    child->currNumKeys += 1;
    childNext->currNumKeys -= 1;
}

void borrowFromNext(struct BTreeNode *node, int index)
{
    struct BTreeNode *child = node->childNodes[index];
    struct BTreeNode *childNext = node->childNodes[index + 1];

    child->keys[child->currNumKeys] = node->keys[index];

    if (!child->isLeaf)
    {
        child->childNodes[child->currNumKeys + 1] = childNext->childNodes[0];
    }

    node->keys[index] = childNext->keys[0];

    for (int i = 1; i < childNext->currNumKeys; ++i)
    {
        childNext->keys[i - 1] = childNext->keys[i];
    }

    if (!child->isLeaf)
    {
        for (int i = 1; i <= childNext->currNumKeys; ++i)
        {
            childNext->childNodes[i - 1] = childNext->childNodes[i];
        }
    }

    child->currNumKeys += 1;
    childNext->currNumKeys -= 1;
}

void merge(struct BTreeNode *node, int index)
{
    // printf("merger index %d\n", index);
    struct BTreeNode *child = node->childNodes[index];
    struct BTreeNode *childNext = node->childNodes[index + 1];

    child->keys[node->degree - 1] = node->keys[index];

    for (int i = 0; i < childNext->currNumKeys; ++i)
    {
        child->keys[i + node->degree - 1] = childNext->keys[i];
    }
    // printf("%d %d %d %d\n", node->childNodes[0]->currNumKeys, node->childNodes[0]->keys[0], node->childNodes[0]->keys[1], node->childNodes[0]->keys[2]);

    if (!child->isLeaf)
    {
        for (int i = 0; i <= childNext->currNumKeys; ++i)
        {
            child->childNodes[i + node->degree - 1] = childNext->childNodes[i];
        }
    }

    for (int i = index + 1; i < node->currNumKeys; ++i)
    {
        node->keys[i - 1] = node->keys[i];
    }

    for (int i = index + 2; i <= node->currNumKeys; ++i)
    {
        node->childNodes[i - 1] = node->childNodes[i];
    }

    child->currNumKeys += childNext->currNumKeys + 1;
    node->currNumKeys--;

    free(childNext);
}

void fill(struct BTreeNode *node, int index)
{
    if (index != 0 && node->childNodes[index - 1]->currNumKeys >= node->degree)
    {
        // printf("fill if\n");
        borrowFromPrev(node, index);
    }
    else if (index != node->currNumKeys && node->childNodes[index + 1]->currNumKeys >= node->degree)
    {
        // printf("fill else if\n");
        borrowFromNext(node, index);
    }
    else
    {
        if (index != node->currNumKeys)
        {
            // printf("fill else last if enter %d\n", node->currNumKeys);
            merge(node, index);
            // printf("fill else last if exit %d\n", node->currNumKeys);
        }
        else
        {
            // printf("fill else last else enter %d\n", node->currNumKeys);
            merge(node, index - 1);
            // printf("fill else last else exit %d\n", node->currNumKeys);
        }
    }
}

struct BTreeNode *removeNodeOnLeaf(struct BTreeNode *node, int index)
{
    // printf("%d %d %d %d\n", node->currNumKeys, node->keys[0], node->keys[1], node->keys[2]);
    // printf("%d %d\n", node->childNodes[0]->currNumKeys, node->childNodes[0]->keys[0]);
    // printf("%d %d\n", node->childNodes[1]->currNumKeys, node->childNodes[1]->keys[0]);
    for (int i = index + 1; i < node->currNumKeys; ++i)
    {
        node->keys[i - 1] = node->keys[i];
    }
    node->currNumKeys--;
    // printf("%d %d %d\n", node->currNumKeys, node->keys[0], node->keys[1]);
    return node;
}

struct BTreeNode *remover(struct BTreeNode *node, int elem)
{
    int index = findIndex(node, elem);
    // printf("remover index %d\n", index);
    if (index < node->currNumKeys && node->keys[index] == elem)
    {
        if (node->isLeaf)
        {
            // printf("remover if if\n");
            struct BTreeNode *res = removeNodeOnLeaf(node, index);
            return res;
        }
        else
        {
            // printf("remover if else\n");
            removeNodeOnNonLeaf(node, index);
        }
    }
    else
    {
        if (node->isLeaf)
        {
            // printf("remover else if1 return\n");
            return;
        }
        bool flag = (index == node->currNumKeys);
        if (node->childNodes[index]->currNumKeys < node->degree - 1)
        {
            // printf("remover else if2\n");
            fill(node, index);
        }
        if (flag && index > node->currNumKeys)
        {
            // printf("remover else if3\n");
            remover(node->childNodes[index - 1], elem);
        }
        else
        {
            // printf("remover else else\n");
            remover(node->childNodes[index], elem);
        }
    }
}

void removeNode(struct BTreeNode **rootNode, int elem)
{
    if (*rootNode == NULL)
    {
        printf("BTree is NULL, cannot be removed!\n");
    }
    else
    {
        struct BTreeNode *tempNode = *rootNode;
        // printf("removeNode else %d\n", tempNode->currNumKeys);
        struct BTreeNode *removeRes = remover(tempNode, elem);
        // printf("removeNode else after remover %d\n", tempNode->currNumKeys);
        if (removeRes->currNumKeys == 0)
        {
            // printf("removeNode else wewewewewe\n");
            struct BTreeNode *delNode = tempNode;
            if (removeRes->isLeaf)
            {
                removeRes = NULL;
            }
            else
            {
                removeRes = removeRes->childNodes[0];
            }
            free(delNode);
        }
        *rootNode = removeRes;
    }
}

void removeNodeOnNonLeaf(struct BTreeNode *node, int index)
{
    int elem = node->keys[index];
    if (node->childNodes[index]->currNumKeys >= node->degree)
    {
        int keyPredecessor = findPredecessorOfIndex(node, index);
        node->keys[index] = keyPredecessor;
        remover(node->childNodes[index], keyPredecessor);
    }
    else if (node->childNodes[index + 1]->currNumKeys >= node->degree)
    {
        int keySuccesor = findSuccessorOfIndex(node, index);
        node->keys[index] = keySuccesor;
        remover(node->childNodes[index], keySuccesor);
    }
    else
    {
        merge(node, index);
        remover(node->childNodes[index], elem);
    }
}

int main()
{
    struct BTreeNode *bTree = NULL;
    printf("//B TREE 1\n");
    search(bTree, 4);
    removeNode(&bTree, 5);
    insert(&bTree, 3, 1);
    insert(&bTree, 3, 2);
    insert(&bTree, 3, 3);
    // printf("%d %d\n", bTree->currNumKeys, bTree->keys[0]);
    // printf("%d %d\n", bTree->childNodes[0]->currNumKeys, bTree->childNodes[0]->keys[0]);
    // printf("%d %d\n", bTree->childNodes[1]->currNumKeys, bTree->childNodes[1]->keys[0]);
    printBTree(bTree);
    printf("\ninsert 4\n");
    insert(&bTree, 3, 4);
    // printf("%d %d\n", bTree->currNumKeys, bTree->keys[0]);
    // printf("%d %d\n", bTree->childNodes[0]->currNumKeys, bTree->childNodes[0]->keys[0]);
    // printf("%d %d\n", bTree->childNodes[1]->currNumKeys, bTree->childNodes[1]->keys[0]);
    printBTree(bTree);
    printf("\ninsert 5\n");
    insert(&bTree, 3, 5);
    // printf("%d %d\n", bTree->currNumKeys, bTree->keys[0]);
    // printf("%d %d\n", bTree->childNodes[0]->currNumKeys, bTree->childNodes[0]->keys[0]);
    // printf("%d %d\n", bTree->childNodes[1]->currNumKeys, bTree->childNodes[1]->keys[0]);
    // printf("%d %d\n", bTree->childNodes[2]->currNumKeys, bTree->childNodes[2]->keys[0]);
    search(bTree, 5);
    search(bTree, 6);
    printBTree(bTree);
    printf("\ninsert 6\n");
    insert2(&bTree, 3, 6);
    // printf("%d %d\n", bTree->currNumKeys, bTree->keys[0]);
    // printf("%d %d\n", bTree->childNodes[0]->currNumKeys, bTree->childNodes[0]->keys[0]);
    // printf("%d %d\n", bTree->childNodes[1]->currNumKeys, bTree->childNodes[1]->keys[0]);
    // printf("%d %d\n", bTree->childNodes[2]->currNumKeys, bTree->childNodes[2]->keys[0]);
    printBTree(bTree);
    printf("\ninsert 7\n");
    insert2(&bTree, 3, 7);
    // printf("%d %d\n", bTree->currNumKeys, bTree->keys[0]);
    // printf("%d %d\n", bTree->childNodes[0]->currNumKeys, bTree->childNodes[0]->keys[0]);
    // printf("%d %d\n", bTree->childNodes[0]->childNodes[0]->currNumKeys, bTree->childNodes[0]->childNodes[0]->keys[0]);
    // printf("%d %d\n", bTree->childNodes[0]->childNodes[1]->currNumKeys, bTree->childNodes[0]->childNodes[1]->keys[0]);
    // printf("%d %d\n", bTree->childNodes[1]->currNumKeys, bTree->childNodes[1]->keys[0]);
    // printf("%d %d\n", bTree->childNodes[1]->childNodes[0]->currNumKeys, bTree->childNodes[1]->childNodes[0]->keys[0]);
    // printf("%d %d\n", bTree->childNodes[1]->childNodes[1]->currNumKeys, bTree->childNodes[1]->childNodes[1]->keys[0]);
    printBTree(bTree);
    printf("\ninsert 8\n");
    insert2(&bTree, 3, 8);
    // printf("%d %d\n", bTree->currNumKeys, bTree->keys[0]);
    // printf("%d %d\n", bTree->childNodes[0]->currNumKeys, bTree->childNodes[0]->keys[0]);
    // printf("%d %d\n", bTree->childNodes[0]->childNodes[0]->currNumKeys, bTree->childNodes[0]->childNodes[0]->keys[0]);
    // printf("%d %d\n", bTree->childNodes[0]->childNodes[1]->currNumKeys, bTree->childNodes[0]->childNodes[1]->keys[0]);
    // printf("%d %d\n", bTree->childNodes[1]->currNumKeys, bTree->childNodes[1]->keys[0]);
    // printf("%d %d\n", bTree->childNodes[1]->childNodes[0]->currNumKeys, bTree->childNodes[1]->childNodes[0]->keys[0]);
    // printf("%d %d\n", bTree->childNodes[1]->childNodes[1]->currNumKeys, bTree->childNodes[1]->childNodes[1]->keys[0]);
    printBTree(bTree);
    printf("\ninsert 9\n");
    insert2(&bTree, 3, 9);
    printf("%d %d\n", bTree->currNumKeys, bTree->keys[0]);
    printf("%d %d\n", bTree->childNodes[0]->currNumKeys, bTree->childNodes[0]->keys[0]);
    printf("%d %d\n", bTree->childNodes[0]->childNodes[0]->currNumKeys, bTree->childNodes[0]->childNodes[0]->keys[0]);
    printf("%d %d\n", bTree->childNodes[0]->childNodes[1]->currNumKeys, bTree->childNodes[0]->childNodes[1]->keys[0]);
    printf("%d %d %d\n", bTree->childNodes[1]->currNumKeys, bTree->childNodes[1]->keys[0], bTree->childNodes[1]->keys[1]);
    printf("%d %d\n", bTree->childNodes[1]->childNodes[0]->currNumKeys, bTree->childNodes[1]->childNodes[0]->keys[0]);
    printf("%d %d\n", bTree->childNodes[1]->childNodes[1]->currNumKeys, bTree->childNodes[1]->childNodes[1]->keys[0]);
    printf("%d %d\n", bTree->childNodes[1]->childNodes[2]->currNumKeys, bTree->childNodes[1]->childNodes[2]->keys[0]);
    search(bTree, 9);
    printBTree(bTree);

    struct BTreeNode *bTree2 = NULL;
    printf("\n\n//B TREE 2\n");
    search(bTree2, 4);
    removeNode(&bTree2, 5);
    insert(&bTree2, 3, 1);
    insert(&bTree2, 3, 2);
    insert(&bTree2, 3, 3);
    printf("%d %d\n", bTree2->currNumKeys, bTree2->keys[0]);
    printf("%d %d\n", bTree2->childNodes[0]->currNumKeys, bTree2->childNodes[0]->keys[0]);
    printf("%d %d\n", bTree2->childNodes[1]->currNumKeys, bTree2->childNodes[1]->keys[0]);
    printBTree(bTree2);
    printf("\n//remove 1\n");
    removeNode(&bTree2, 1);
    // printf("%d %d %d\n", bTree2->currNumKeys, bTree2->keys[0], bTree2->keys[0]);
    printBTree(bTree2);
    printf("\n//remove 2\n");
    removeNode(&bTree2, 2);
    // printf("%d %d %d\n", bTree2->currNumKeys, bTree2->keys[0], bTree2->keys[0]);
    printBTree(bTree2);
    printf("\n//remove 3\n");
    removeNode(&bTree2, 3);
    printBTree(bTree2);
    printf("\n//remove non-existing element 4\n");
    removeNode(&bTree2, 4);
}