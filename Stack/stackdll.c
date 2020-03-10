#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../ADT/doublylinklist.h"

void push(struct DoublyLinkListNode **head_pointer, int new_elem)
{
    struct DoublyLinkListNode *new_node = (struct DoublyLinkListNode *)malloc(sizeof(struct DoublyLinkListNode));
    new_node->next = *head_pointer;
    new_node->prev = NULL;
    new_node->elem = new_elem;
    if ((*head_pointer) != NULL)
        (*head_pointer)->prev = new_node;
    *head_pointer = new_node;
}

void pop(struct DoublyLinkListNode **head_pointer)
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

void peek(struct DoublyLinkListNode *head_pointer)
{
    if (head_pointer != NULL)
    {
        printf("\nElement on top of the stack is %d", head_pointer->elem);
    }
    else
    {
        printf("\nStack is Empty!");
    }
}

void printStack(struct DoublyLinkListNode *head_pointer)
{
    if (head_pointer != NULL)
    {
        struct DoublyLinkListNode *last;
        printf("\nStack:");
        while (head_pointer != NULL)
        {
            printf(" %d ", head_pointer->elem);
            last = head_pointer;
            head_pointer = head_pointer->next;
        }
    }
    else
    {
        printf("\nStack is Empty!");
    }
}

int main()
{
    struct DoublyLinkListNode *stack = NULL;
    peek(stack);
    push(&stack, 5);
    printStack(stack);
    push(&stack, 4);
    printStack(stack);
    push(&stack, 5);
    printStack(stack);
    pop(&stack);
    printStack(stack);
    peek(stack);
    push(&stack, 3);
    printStack(stack);
    push(&stack, 2);
    printStack(stack);
    push(&stack, 1);
    printStack(stack);
    peek(stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);
    printStack(stack);
    pop(&stack);
    printStack(stack);
}
