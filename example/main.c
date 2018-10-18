#include "main.h"

int main()
{
    HeapNode node, poppedNode;

    BinaryHeap* myHeap = binary_heap_create();

    node.key = 11; strcpy(node.name, "Node A");
    binary_heap_push(&myHeap, node);
    node.key = 5; strcpy(node.name, "Node B");
    binary_heap_push(&myHeap, node);
    node.key = 8; strcpy(node.name, "Node C");
    binary_heap_push(&myHeap, node);
    node.key = 3; strcpy(node.name, "Node D");
    binary_heap_push(&myHeap, node);
    node.key = 4; strcpy(node.name, "Node E");
    binary_heap_push(&myHeap, node);
    printHeap(myHeap);

    node.key = 15; strcpy(node.name, "Node F");
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

void printPoppedNode(HeapNode* node)
{
    if (node == NULL)
    {
        printf("\nNull Node\n");
        return;
    }

    printf("\npoppedNode -> key:%i, name:%s\n", node->key, node->name);
}

void printHeap(BinaryHeap* bHeap)
{
    if (bHeap == NULL)
    {
        printf("\nNull Heap\n");
        return;
    }

    printf("\n\n## BinaryHeap Size: %zu\n", bHeap->size);
    for(int i=0; i<bHeap->size;i++)
        printf("[%i] -> key:%i, name:%s\n", i, bHeap->nodes[i].key, bHeap->nodes[i].name);
}
