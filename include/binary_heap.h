#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief This struct represents a binary heap node which is composed by a heap key and
 *        by a name that identifies it.
 */
typedef struct heapNode
{
    int key; /**< Heap key of the node. */
    char name[50]; /**< Name of the node. */

} heapNode;

/**
 * @brief This struct represents a binary heap which is composed by a size value, which
 *        represents the number of nodes on the heap, and by a pointer to its nodes.
 *        The size of the heap is automatically updated during push and pop operations.
 */
typedef struct binaryHeap
{
    heapNode* nodes; /**< Pointer to the nodes of the heap. */
    size_t size; /**< Size of the heap. */

} binaryHeap;

/**
 * @brief Creates and initializes a binary heap. The size of the binary heap is
 *        set to 0 and the pointer to its nodes is set to NULL.
 *
 * @return Returns a pointer to the binary heap created.
 */
binaryHeap* binary_heap_create();

/**
 * @brief Deallocates the memory allocated for the heap nodes and for the binary
 *        heap to prevent memory leaks. It also sets the pointer to the heap to NULL.
 *
 * @param bHeap Pointer to the pointer of the binary heap to be destroyed.
 */
void binary_heap_destroy(binaryHeap** bHeap);

/**
 * @brief Pushes a heap node in a given binary heap, and if necessary reorganizes the
 *        heap to maintain the heap property. It also updates the size of the heap.
 *
 * @param bHeap Pointer to the pointer of the binary heap in which the heap node is meant to be pushed.
 * @param node Heap node to be pushed into the binary heap.
 * @return Returns 0 in case of sucess and -1 otherwise.
 */
int binary_heap_push(binaryHeap** bHeap, heapNode node);

/**
 * @brief Returns the top heap node, removes it from the binary heap and reorders the heap.
 *        It also updates the size of the heap.
 *
 * @param bHeap Pointer to the pointer of the binary heap from which the node is meant to be popped.
 * @return Returns the top node from the binary heap in case of success and a node with a heap key equal to -1 otherwise
 */
heapNode binary_heap_pop(binaryHeap** bHeap);

/**
 * @brief This method allows to access the top heap node without altering the state of
 *        the binary heap.
 *
 * @param bHeap Pointer to the binary heap to be analyzed.
 * @return Returns a pointer to the top node in case of success and a NULL pointer otherwise.
 */
heapNode* binary_heap_peek(binaryHeap* bHeap);

/**
 * @brief Returns the size of a given binary heap.
 *
 * @param bHeap Pointer to the binary heap to be analyzed.
 * @return Returns the size of the binary or -1 if the pointer to the heap is NULL.
 */
int binary_heap_get_size(binaryHeap* bHeap);

#endif
