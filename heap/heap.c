#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

Heap* createHeap(int maxElementCount) {
    Heap* pHeap;

    if (maxElementCount <= 0) {
        printf("maxElementCount ERROR\n");
        return (NULL);
    }
    pHeap = (Heap*)malloc(sizeof(Heap));
    pHeap->maxElementCount = maxElementCount;
    pHeap->currentElementCount = 0;
    pHeap->pElement = (HeapNode*)malloc(sizeof(HeapNode) * maxElementCount);
    return (pHeap);
}

int insertHeap(Heap* pHeap, int data) {
    return (TRUE);
}

HeapNode* deleteHeapNode(Heap* pHeap) {
    return (NULL);
}

void deleteHeap(Heap* pHeap) {
    return ;
}

int main() {
    Heap* pHeap;

    pHeap = createHeap(100);
}