#include <stdio.h>
#include <string.h>

#include "binary_heap.h"

/**
 * @brief Prints the content of a given binary heap in a form of an array.
 *        If the pointer to the heap is NULL it prints the message 'Null Heap'.
 *
 * @param bHeap Pointer to the binary heap to be printed.
 */
void printHeap(binaryHeap* bHeap);

/**
 * @brief Prints the content of a popped node. If the pointer to the heap is
 *        NULL it prints the message 'Null Node'.
 *
 * @param node Pointer to the node to be printed
 */
void printPoppedNode(heapNode* node);
