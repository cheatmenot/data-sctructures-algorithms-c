#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../ADT/doublylinklist.h"

//https://stackoverflow.com/questions/766893/how-do-i-modify-a-pointer-that-has-been-passed-into-a-function-in-c
void insertHead(struct DoublyLinkListNode **head_pointer, int new_elem){
    struct DoublyLinkListNode* new_node = (struct DoublyLinkListNode*)malloc(sizeof(struct DoublyLinkListNode));
    new_node->next = *head_pointer;
    new_node->prev = NULL;
    new_node->elem = new_elem;
    if ((*head_pointer) != NULL) 
        (*head_pointer)->prev = new_node; 
    *head_pointer = new_node;
}

void insertTail(struct DoublyLinkListNode **head_pointer, int new_elem){
    struct DoublyLinkListNode* new_node = (struct DoublyLinkListNode*)malloc(sizeof(struct DoublyLinkListNode));
    struct DoublyLinkListNode* last;
    struct DoublyLinkListNode* list = *head_pointer;
    while (list != NULL) {   
        last = list;  
        list = list->next;  
    }  
    new_node->next = NULL;
    new_node->prev = last;
    new_node->elem = new_elem;
    last->next = new_node;
}

void insertBefore(struct DoublyLinkListNode **head_pointer, struct DoublyLinkListNode *currNode, int new_elem){
    struct DoublyLinkListNode* new_node = (struct DoublyLinkListNode*)malloc(sizeof(struct DoublyLinkListNode));
    new_node->elem = new_elem;
    new_node->next = currNode;
    new_node->prev = currNode->prev;

    if (currNode->prev != NULL) 
        currNode->prev->next = new_node; 
    currNode->prev = new_node;

    if(new_node->prev == NULL){
        *head_pointer = new_node;
    }
}

void insertAfter(struct DoublyLinkListNode *prev_node, int new_elem){
    struct DoublyLinkListNode* new_node = (struct DoublyLinkListNode*)malloc(sizeof(struct DoublyLinkListNode));
    new_node->elem = new_elem; 
    new_node->next = prev_node->next;
    new_node->prev = prev_node;

    prev_node->next = new_node; 
    if (new_node->next != NULL) 
        new_node->next->prev = new_node; 
}

void deleteHead(struct DoublyLinkListNode **head_pointer){
    struct DoublyLinkListNode* del_node = *head_pointer;
    del_node->next->prev = NULL;
    *head_pointer = del_node->next;
    free(del_node);
}

void delete(struct DoublyLinkListNode **head_pointer, struct DoublyLinkListNode *deleteNode){
    if(deleteNode->next != NULL){
        deleteNode->next->prev = deleteNode->prev;
    }
    if(deleteNode->prev != NULL){
        deleteNode->prev->next = deleteNode->next;
    } 

    if(deleteNode->prev == NULL){
        *head_pointer = deleteNode->next;
    }  
    
    free(deleteNode);
}

void view(struct DoublyLinkListNode *head_pointer, int position){
    struct DoublyLinkListNode* before = head_pointer;
    for(int i = 0; i < position; i++){
        before = before->next;
    }
    printf("\nElement in position %d is %d", position, before->elem); 
}

void viewNode(struct DoublyLinkListNode *head_pointer, int position){
    struct DoublyLinkListNode* before = head_pointer;
    for(int i = 0; i < position; i++){
        before = before->next;
    }
    printf("\nNode in position %d is %d, %p, %p", position, before->elem, before->prev, before->next); 
}

struct DoublyLinkListNode* getNode(struct DoublyLinkListNode *head_pointer, int position){
    struct DoublyLinkListNode* before = head_pointer;
    for(int i = 0; i < position; i++){
        before = before->next;
    }
    return before;
}

void printList(struct DoublyLinkListNode* list)  
{  
    struct DoublyLinkListNode* last;  
    printf("\nList:");  
    while (list != NULL) {  
        printf(" %d ", list->elem);  
        last = list;  
        list = list->next;  
    }  
}

int main() {
    struct DoublyLinkListNode* list = NULL;
    insertHead(&list, 5);
    printList(list);
    insertHead(&list, 4);
    printList(list);
    insertHead(&list, 3);
    printList(list);
    view(list, 2);
    struct DoublyLinkListNode* curr = getNode(list, 2);
    insertBefore(&list, curr, 8);
    // insertAfter(curr, 8);
    printList(list);
    insertTail(&list, 1);
    printList(list);
    deleteHead(&list);
    printList(list);
    viewNode(list, 1);
    struct DoublyLinkListNode* deleteIndexOne = getNode(list, 1);
    delete(&list, deleteIndexOne);
    printList(list);
    struct DoublyLinkListNode* deleteLastIndex = getNode(list, 2);
    delete(&list, deleteLastIndex);
    printList(list);
    struct DoublyLinkListNode* deleteFirstIndex = getNode(list, 0);
    delete(&list, deleteFirstIndex);
    printList(list);
   

    // struct DoublyLinkListNode* list = NULL;
    // insertBefore(&list, NULL, 1);
}




