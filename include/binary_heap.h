#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

/**
 * @brief This struct represents a binary heap node which is composed by a key and
 *        an abstract item.
 */
typedef struct HeapNode
{
    int key; /**< Key of the node. */
    void *item; /**< Pointer to the object being kept by the node. */
} HeapNode;

/**
 * @brief This is the signature of the function that should be used to deallocate an item from
 *        a HeapNode.
 */
typedef void (*BinaryHeapCollector)(void * item);

/**
 * @brief This struct represents a binary heap which is composed by a size value, which
 *        represents the number of nodes on the heap, and by a pointer to its nodes.
 *        The size of the heap is automatically updated during push and pop operations.
 */
typedef struct BinaryHeap
{
    HeapNode* nodes; /**< Pointer to the nodes of the heap. */
    BinaryHeapCollector collect; /**< Pointer to the item deallocation function. */
    size_t size; /**< Size of the heap. */

} BinaryHeap;

/**
 * @brief Creates and initializes a binary heap. The size of the binary heap is
 *        set to 0 and the pointer to its nodes is set to NULL.
 *
 * @param collector Pointer to the function to be used when deallocating items from the binary heap.
 *                  If the items stored on the binary heap were not allocated on the Heap memory
 *                  they should not be deallocated. If this is the case the collector can be set to NULL.
 *
 * @return Returns a pointer to the binary heap created.
 */
BinaryHeap* binary_heap_create(BinaryHeapCollector collector);

/**
 * @brief Deallocates the memory allocated for the heap nodes and for the binary
 *        heap to prevent memory leaks. It uses the collector function, given when
 *        the binary heap was created, to deallocate the node's items. It also sets
 *        the pointer to the heap to NULL.
 *
 * @param bHeap Pointer to the pointer of the binary heap to be destroyed.
 */
void binary_heap_destroy(BinaryHeap** bHeap);

/**
 * @brief Pushes a heap node in a given binary heap, and if necessary reorganizes the
 *        heap to maintain the heap property. It also updates the size of the heap.
 *
 * @param bHeap Pointer to the pointer of the binary heap in which the heap node is meant to be pushed.
 * @param node Heap node to be pushed into the binary heap.
 * @return Returns 0 in case of sucess and -1 otherwise.
 */
int binary_heap_push(BinaryHeap** bHeap, HeapNode node);

/**
 * @brief Returns the top heap node, removes it from the binary heap and reorders the heap.
 *        It also updates the size of the heap.
 *
 * @param bHeap Pointer to the pointer of the binary heap from which the node is meant to be popped.
 * @return Returns the top node from the binary heap in case of success and a node with a heap key equal to -1 otherwise
 */
HeapNode binary_heap_pop(BinaryHeap** bHeap);

/**
 * @brief This method allows to access the top heap node without altering the state of
 *        the binary heap.
 *
 * @param bHeap Pointer to the binary heap to be analyzed.
 * @return Returns a pointer to the top node in case of success and a NULL pointer otherwise.
 */
HeapNode* binary_heap_peek(BinaryHeap* bHeap);

#endif
