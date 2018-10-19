#include <stdio.h>
#include <string.h>

#include "binary_heap.h"

static void printHeap(BinaryHeap* bHeap);
static void printPoppedNode(HeapNode* node);


int main()
{
    HeapNode node, poppedNode;

    BinaryHeap* myHeap = binary_heap_create(NULL);

    node.key = 11; strcpy(node.item, "Node A");
    binary_heap_push(&myHeap, node);
    node.key = 5; strcpy(node.item, "Node B");
    binary_heap_push(&myHeap, node);
    node.key = 8; strcpy(node.item, "Node C");
    binary_heap_push(&myHeap, node);
    node.key = 3; strcpy(node.item, "Node D");
    binary_heap_push(&myHeap, node);
    node.key = 4; strcpy(node.item, "Node E");
    binary_heap_push(&myHeap, node);
    printHeap(myHeap);

    node.key = 15; strcpy(node.item, "Node F");
    binary_heap_push(&myHeap, node);
    printHeap(myHeap);

    poppedNode = binary_heap_pop(&myHeap);
    printPoppedNode(&poppedNode);
    printHeap(myHeap);

    poppedNode = binary_heap_pop(&myHeap);
    printPoppedNode(&poppedNode);
    printHeap(myHeap);

    poppedNode = binary_heap_pop(&myHeap);
    printPoppedNode(&poppedNode);
    printHeap(myHeap);

    poppedNode = binary_heap_pop(&myHeap);
    printPoppedNode(&poppedNode);
    printHeap(myHeap);

    poppedNode = binary_heap_pop(&myHeap);
    printPoppedNode(&poppedNode);
    printHeap(myHeap);

    poppedNode = binary_heap_pop(&myHeap);
    printPoppedNode(&poppedNode);
    printHeap(myHeap);

    binary_heap_destroy(&myHeap);
    printHeap(myHeap);

    return 0;
}

static void printPoppedNode(HeapNode* node)
{
    if (node == NULL)
    {
        printf("\nNull Node\n");
        return;
    }

    printf("\npoppedNode -> key:%i, name:%s\n", node->key, node->item);
}

static void printHeap(BinaryHeap* bHeap)
{
    if (bHeap == NULL)
    {
        printf("\nNull Heap\n");
        return;
    }

    printf("\n\n## BinaryHeap Size: %zu\n", bHeap->size);
    for(int i=0; i<bHeap->size;i++)
        printf("[%i] -> key:%i, name:%s\n", i, bHeap->nodes[i].key, bHeap->nodes[i].item);
}
