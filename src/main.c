#include "main.h"

int main(int argc, char** argv[])
{
    heapNode node, poppedNode;

    binaryHeap* myHeap = create();

    node.key = 11; strcpy(node.name, "Node A");
    push(&myHeap, node);
    node.key = 5; strcpy(node.name, "Node B");
    push(&myHeap, node);
    node.key = 8; strcpy(node.name, "Node C");
    push(&myHeap, node);
    node.key = 3; strcpy(node.name, "Node D");
    push(&myHeap, node);
    node.key = 4; strcpy(node.name, "Node E");
    push(&myHeap, node);

    printHeap(myHeap);

    node.key = 15; strcpy(node.name, "Node F");
    push(&myHeap, node);
    printHeap(myHeap);



    poppedNode = pop(&myHeap);
    printPoppedNode(&poppedNode);
    printHeap(myHeap);

    poppedNode = pop(&myHeap);
    printPoppedNode(&poppedNode);
    printHeap(myHeap);

    poppedNode = pop(&myHeap);
    printPoppedNode(&poppedNode);
    printHeap(myHeap);

    poppedNode = pop(&myHeap);
    printPoppedNode(&poppedNode);
    printHeap(myHeap);

    poppedNode = pop(&myHeap);
    printPoppedNode(&poppedNode);
    printHeap(myHeap);

    poppedNode = pop(&myHeap);
    printPoppedNode(&poppedNode);
    printHeap(myHeap);

    destroy(&myHeap);
    myHeap = NULL;
    printHeap(myHeap);

    return 0;
}

void printPoppedNode(heapNode* node)
{
    if (node == NULL)
    {
        printf("\nNull Node\n");
        return;
    }

    printf("\npoppedNode -> key:%i, name:%s\n", node->key, node->name);
}

void printHeap(binaryHeap* bHeap)
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
