#ifndef __DOUBLYLINKLISTNODE_H
#define __DOUBLYLINKLISTNODE_H

struct DoublyLinkListNode {
    int elem;
    struct DoublyLinkListNode *prev;
    struct DoublyLinkListNode *next;
} doublyLinkListNode;

#endif