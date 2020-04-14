#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../ADT/binarytreenode.h"

struct BinaryTreeNode *splayer(struct BinaryTreeNode *node, int elem){
    if(node->elem == elem){
        return node;
    }
    else if(node->elem > elem){
        if(node->left == NULL){
            return node;
        }
        if(node->left->left != NULL && node->left->elem > elem){
            printf("Left Left Case: %d, %d\n", elem, node->elem);
            node->left->left = splayer(node->left->left, elem);
            node = rotateRight(node);
        }
        else if(node->left->right != NULL && node->left->elem < elem){
            printf("Left Right Case: %d, %d\n", elem, node->left->elem);
            node->left->right  = splayer(node->left->right, elem);
            if(node->left->right != NULL){
                node->left = rotateLeft(node->left);
            }
        }
        struct BinaryTreeNode *temp_node = (node->left == NULL) ? node : rotateRight(node);
        return temp_node;
    }
    else if (node->elem < elem){
        if(node->right == NULL){
            return node;
        }
        if(node->right->right != NULL && node->right->elem < elem){
            printf("Right Right Case: %d, %d\n", elem, node->elem);
            node->right->right = splayer(node->right->right, elem);
            node = rotateLeft(node);
        }
        else if(node->right->left != NULL && node->right->elem > elem){
            printf("Right Left Case: %d, %d\n", elem, node->right->elem);
            node->right->left = splayer(node->right->left, elem);
            if(node->right->left != NULL){
                node->right = rotateRight(node->right);
            }
        }
        struct BinaryTreeNode *temp_node = (node->right == NULL) ? node : rotateLeft(node);
        return temp_node;
    }
    else {
        return node;
    }
}

void *search(struct BinaryTreeNode **root_pointer, int elem){
    if(*root_pointer != NULL){
        *root_pointer = splayer(*root_pointer, elem);
    }
    else {
        printf("Cannot splay empty splay tree!\n");
    }
}

void *insert(struct BinaryTreeNode **root_node, int elem){
    if(*root_node == NULL) {
        struct BinaryTreeNode *new_node = newNode(elem);
        *root_node = new_node;
    }
    else {
        struct BinaryTreeNode *temp_node = splayer(*root_node, elem);
        struct BinaryTreeNode *new_node = newNode(elem);
        if (temp_node->elem == elem) {
            *root_node = temp_node;
        }
        else if(temp_node->elem > elem){
            new_node->right = temp_node;
            new_node->left = temp_node->left;
            temp_node->left = NULL;
            temp_node->parent = new_node;
        }
        else if(temp_node->elem < elem){
            new_node->left = temp_node;
            new_node->right = temp_node->right;
            temp_node->right = NULL;
            temp_node->parent = new_node;
        }
        *root_node = new_node;
    }
}

void *delete(struct BinaryTreeNode **root_node, int elem){
    if(*root_node == NULL) {
        printf("Splay Tree Node is empty\n");
    }
    else {
        struct BinaryTreeNode *temp_node = splayer(*root_node, elem);
        struct BinaryTreeNode *del_node;

        if(temp_node->elem != elem) {
            printf("Cannot find element %d on the splay tree!\n", elem);
        }
        else {
            if(temp_node->left == NULL){
                del_node = temp_node;
                temp_node = temp_node->right;
            }
            else {
                del_node = temp_node;
                temp_node = splayer(temp_node->left, elem); 
                temp_node->right = del_node->right;
            }
            free(del_node);
        }
        *root_node = temp_node;
    }
}

int main()
{
    struct BinaryTreeNode *splay_tree = NULL;
    printf("//Splay Tree 1\n");
    printTreeFromRootToLeaf(splay_tree);
    printf("//insert element 1, 2, 3, 15, 8, 10\n");
    insert(&splay_tree, 1);
    insert(&splay_tree, 2);
    insert(&splay_tree, 3);
    insert(&splay_tree, 15);
    insert(&splay_tree, 8);
    insert(&splay_tree, 10);
    printTreeFromRootToLeaf(splay_tree);
    printf("//search 1\n");
    search(&splay_tree, 1);
    printTreeFromRootToLeaf(splay_tree);
    printf("//delete 8\n");
    delete(&splay_tree, 8);
    printTreeFromRootToLeaf(splay_tree);
    printf("//delete 0\n");
    delete(&splay_tree, 3);
    delete(&splay_tree, 2);
    delete(&splay_tree, 10);
    printTreeFromRootToLeaf(splay_tree);
    printf("//delete non existing element 7\n");
    delete(&splay_tree, 7);
    printTreeFromRootToLeaf(splay_tree);
    printf("//delete 1, 15\n");
    delete(&splay_tree, 1);
    delete(&splay_tree, 15);
    printf("//search/delete to null node\n");
    search(&splay_tree, 5);
    delete(&splay_tree, 5);

    // struct BinaryTreeNode *splay_tree2 = NULL;
    // printf("//Splay Tree 2\n");
    // printTreeFromRootToLeaf(splay_tree2);
    // splay_tree2 = newNode(6);
    // splay_tree2->left = newNode(1);  
    // splay_tree2->right = newNode(9);  
    // splay_tree2->left->right = newNode(4);  
    // splay_tree2->left->right->left = newNode(2);  
    // splay_tree2->right->left = newNode(7); 
    // printTreeFromRootToLeaf(splay_tree2);
    // delete(&splay_tree2, 4);
    // printTreeFromRootToLeaf(splay_tree2);
}