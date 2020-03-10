#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../ADT/doublylinklist.h"

void enqueue(struct DoublyLinkListNode **head_pointer, int new_elem)
{
    struct DoublyLinkListNode *new_node = (struct DoublyLinkListNode *)malloc(sizeof(struct DoublyLinkListNode));
    if (*head_pointer == NULL)
    {
        new_node->next = NULL;
        new_node->prev = NULL;
        new_node->elem = new_elem;
        *head_pointer = new_node;
    }
    else
    {
        struct DoublyLinkListNode *last;
        struct DoublyLinkListNode *list = *head_pointer;
        while (list != NULL)
        {
            last = list;
            list = list->next;
        }
        new_node->next = NULL;
        new_node->prev = last;
        new_node->elem = new_elem;
        last->next = new_node;
    }
}

void dequeue(struct DoublyLinkListNode **head_pointer)
{
    if (*head_pointer != NULL)
    {
        struct DoublyLinkListNode *del_node = *head_pointer;
        if (del_node->next != NULL)
        {
            del_node->next->prev = NULL;
            *head_pointer = del_node->next;
        }
        else
        {
            *head_pointer = NULL;
        }
        free(del_node);
    }
    else
    {
        printf("\nQueue is Empty, No Element to Dequeue!");
    }
}

void view(struct DoublyLinkListNode *head_pointer)
{
    if (head_pointer != NULL)
    {
        printf("\nElement next in line in the queue is %d", head_pointer->elem);
    }
    else
    {
        printf("\nQueue is Empty!");
    }
}

void printQueue(struct DoublyLinkListNode *head_pointer)
{
    if (head_pointer != NULL)
    {
        struct DoublyLinkListNode *last;
        printf("\nQueue:");
        while (head_pointer != NULL)
        {
            printf(" %d ", head_pointer->elem);
            last = head_pointer;
            head_pointer = head_pointer->next;
        }
    }
    else
    {
        printf("\nQueue is Empty!");
    }
}

int main()
{
    struct DoublyLinkListNode *queue = NULL;
    printQueue(queue);
    enqueue(&queue, 5);
    printQueue(queue);
    enqueue(&queue, 1);
    printQueue(queue);
    enqueue(&queue, 2);
    view(queue);
    printQueue(queue);
    dequeue(&queue);
    printQueue(queue);
    enqueue(&queue, 3);
    printQueue(queue);
    dequeue(&queue);
    dequeue(&queue);
    dequeue(&queue);
    printQueue(queue);
    dequeue(&queue);
}