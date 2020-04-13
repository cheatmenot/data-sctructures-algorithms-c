#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../ADT/arraycompletetree.h"

void swap(int *int_a, int *int_b)
{
    int temp_int = *int_a;
    *int_a = *int_b;
    *int_b = temp_int;
}

int getParent(int current_index)
{
    return (current_index - 1) / 2;
}

int getLeft(int current_index)
{
    return (2 * (current_index) + 1);
}

int getRight(int current_index)
{
    return (2 * (current_index) + 2);
}

void insert(struct ArrayCompleteTree *array_complete_tree, int elem)
{
    int size = array_complete_tree->size;
    int *intArray = array_complete_tree->heapArray;

    array_complete_tree->size++;
    array_complete_tree->heapArray[size] = elem;

    int temp = size;

    while (temp != 0 && intArray[getParent(temp)] > intArray[temp])
    {
        swap(&intArray[temp], &intArray[getParent(temp)]);
        temp = getParent(temp);
    }
}

void heapify(struct ArrayCompleteTree *array_complete_tree, int index)
{
    int size = array_complete_tree->size;
    int *intArray = array_complete_tree->heapArray;

    int temp = index;
    int right_index = getRight(index);
    int left_index = getLeft(index);
    if (left_index < size && intArray[left_index] < intArray[index])
        temp = left_index;
    if (right_index < size && intArray[right_index] < intArray[temp])
        temp = right_index;
    if (temp != index)
    {
        swap(&intArray[index], &intArray[temp]);
        heapify(array_complete_tree, temp);
    }
}

void removeMin(struct ArrayCompleteTree *array_complete_tree)
{
    int size = array_complete_tree->size;
    int *intArray = array_complete_tree->heapArray;

    int last_element = intArray[size - 1];
    intArray[0] = last_element;

    heapify(array_complete_tree, 0);

    array_complete_tree->size--;
}

void printArray(struct ArrayCompleteTree *array_complete_tree)
{
    int size = array_complete_tree->size;
    int *intArray = array_complete_tree->heapArray;
    printf("{");
    for (int i = 0; i < size; i++)
    {
        if (i < (size - 1))
        {
            printf("%d, ", intArray[i]);
        }
        else if (i == (size - 1))
        {
            printf("%d", intArray[i]);
        }
    }
    printf("}\n");
}

int main()
{
    struct ArrayCompleteTree array_complete_tree = {0};
    printf("Size is %d\n", array_complete_tree.size);
    printArray(&array_complete_tree);
    insert(&array_complete_tree, 10);
    printArray(&array_complete_tree);
    insert(&array_complete_tree, 4);
    printArray(&array_complete_tree);
    insert(&array_complete_tree, 6);
    printArray(&array_complete_tree);
    insert(&array_complete_tree, 1);
    printArray(&array_complete_tree);
    insert(&array_complete_tree, 9);
    printArray(&array_complete_tree);
    insert(&array_complete_tree, 8);
    printArray(&array_complete_tree);
    insert(&array_complete_tree, 7);
    printArray(&array_complete_tree);
    removeMin(&array_complete_tree);
    printArray(&array_complete_tree);
    removeMin(&array_complete_tree);
    printArray(&array_complete_tree);
    removeMin(&array_complete_tree);
    printArray(&array_complete_tree);
    removeMin(&array_complete_tree);
    printArray(&array_complete_tree);
}