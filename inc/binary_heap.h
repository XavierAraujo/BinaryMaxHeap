
typedef struct binaryHeap
{
    node* nodes;
    int size;

} binaryHeap;

typedef struct node
{
    int key;
    char name[50];

} node;


binaryHeap* create();

int size(binaryHeap* bHeap);
