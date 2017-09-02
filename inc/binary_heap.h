#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief This struct represents a binary heap node which is composed by a heap key and by a name that identifies it.
 *
 */
typedef struct heapNode
{
    int key; /**< Heap key of the node. */
    char name[50]; /**< Name of the node. */

} heapNode;

/**
 * @brief This struct represents a binary heap which is composed by a size value which represents the number of nodes on the heap and by a pointer to its nodes.
 *
 */
typedef struct binaryHeap
{
    heapNode* nodes; /**< Pointer to the nodes of the heap. */
    size_t size; /**< Size of the heap. */

} binaryHeap;

/**
 * @brief create Creates and initializes a binary heap. The size of the binary heap is set to 0 and it has no nodes.
 * @return Returns a pointer to the binary heap created.
 */
binaryHeap* create();

/**
 * @brief destroy Deallocates the memory allocated for the heap nodes and for the binary heap to prevent memory leaks. It also set the pointer to NULL.
 * @param bHeap Pointer to the binary heap to be destroyed.
 */
void destroy(binaryHeap** bHeap);

/**
 * @brief push Pushes a heap node in a given binary heap, and reorganizes the heap if necessary to maintain the heap property.
 * @param bHeap Pointer to the binary heap in which the heap node is meant to be pushed.
 * @param node Heap node to be pushed into the binary heap
 * @return
 */
int push(binaryHeap** bHeap, heapNode node);

/**
 * @brief pop Returns the top heap node, removes it from the binary heap and reorders the heap.
 * @param bHeap Pointer to the binary heap from which the node is meant to be popped.
 * @return Returns the top node from the binary heap.
 */
heapNode pop(binaryHeap** bHeap);

/**
 * @brief peek This method allows to access the top heap node without altering the state of the binary heap.
 * @param bHeap Pointer to the binary heap to be analyzed.
 * @return Returns a pointer to the top node.
 */
heapNode* peek(binaryHeap* bHeap);

/**
 * @brief size Gives the size of a given binary heap.
 * @param bHeap Pointer to the binary heap to be analyzed.
 * @return Returns the size of the binary or -1 if the pointer to the heap is NULL.
 */
int size(binaryHeap* bHeap);

/**
 * @brief reorderAfterPush Reorganizes the binary heap after a new element being pushed.
 * This function must only be called after a push procedure and so it is declared as static to provide some encapsulation.
 * @param bHeap Pointer to the binary heap to be reorganized.
 */
static void reorderAfterPush(binaryHeap* bHeap);

/**
 * @brief reorderAfterPush Reorganizes the binary heap after a element being popped.
 * This function must only be called after a pop procedure and so it is declared as static to provide some encapsulation.
 * @param bHeap Pointer to the binary heap to be reorganized.
 */
static void reorderAfterPop(binaryHeap* bHeap);

/**
 * @brief hasChilds Analyzes if a given node has child nodes
 * @param bHeap Pointer to the heap to be analyzed.
 * @param nodeIndex Index of the node to be analyzed.
 * @return Returns true if the node has at least one child and false otherwise.
 */
static bool hasChilds(binaryHeap* bHeap, int nodeIndex);

/**
 * @brief isParentKeyLowerThanChild Analyzes if the childs of a given node have a higher heap key.
 * @param bHeap Pointer to the heap to be analyzed.
 * @param parentIndex Index of the parent to be analyzed.
 * @return Returns true if one of the childs of the indicated parent has a higher key than the parent, and false otherwise.
 */
static bool isParentKeyLowerThanChild(binaryHeap* bHeap, int parentIndex);

/**
 * @brief getHighestKeyChild Analyzes the childs of a parent node and it returns the index of the one with the hightes key
 * @param bHeap Pointer to the heap to be analyzed.
 * @param parentIndex Index of the parent to be analyzed.
 * @return Returns the index of the child containing the highest key value.
 */
static int getIndexOfHighestKeyChild(binaryHeap* bHeap, int parentIndex);

/**
 * @brief swap Swaps two elements from the binary heap. Note that the index of the first element is 0.
 * @param bHeap Pointer to the binary heap in which the heap nodes are meant to be swapped.
 * @param index1 Index of the first heap node.
 * @param index2 Index of the second heap node.
 */
static void swap(binaryHeap* bHeap, int index1, int index2);

#endif
