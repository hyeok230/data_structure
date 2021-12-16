#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

Heap* createHeap(int maxElementCount) {
    Heap* pHeap;

    if (maxElementCount <= 0) {
        printf("maxElementCount ERROR\n");
        return (NULL);
    }
    pHeap = (Heap*)malloc(sizeof(Heap));
    pHeap->maxElementCount = maxElementCount;
    pHeap->currentElementCount = 0; 
    pHeap->pElement = (HeapNode*)malloc(sizeof(HeapNode) * (maxElementCount + 1));
    memset(pHeap->pElement, 0, sizeof(HeapNode) * (pHeap->maxElementCount + 1));
    return (pHeap);
}

int insertMaxHeap(Heap* pHeap, HeapNode element) {
    int i;
    HeapNode* newNode;
    
    if (pHeap == NULL) {
        printf("pHeap ERROR\n");
        return (FALSE);
    }
    if (isHeapFull(pHeap)) {
        printf("pHeap full ERROR\n");
        return (FALSE);
    }
    pHeap->currentElementCount++;
    i = pHeap->currentElementCount;
    while(i > 1 && element.data > pHeap->pElement[i / 2].data) {
        pHeap->pElement[i] = pHeap->pElement[i/2];
        i = i / 2;
    }
    pHeap->pElement[i] = element;
    return (TRUE);
}

int insertMinHeap(Heap* pHeap, HeapNode element) {
    int i;
    HeapNode* newNode;
    
    if (pHeap == NULL) {
        printf("pHeap ERROR\n");
        return (FALSE);
    }
    if (isHeapFull(pHeap)) {
        printf("pHeap full ERROR\n");
        return (FALSE);
    }
    pHeap->currentElementCount++;
    i = pHeap->currentElementCount;
    while(i > 1 && element.data < pHeap->pElement[i/2].data) {
        pHeap->pElement[i] = pHeap->pElement[i/2];
        i = i / 2;
    }
    pHeap->pElement[i] = element;
    return (TRUE);
}

int isHeapFull(Heap* pHeap) {
    if (pHeap == NULL) {
        printf("pHeap ERROR\n");
        return (FALSE);
    }
    if (pHeap->currentElementCount == pHeap->maxElementCount) {
        return (TRUE);
    }
    return (FALSE);
}

int isHeapEmpty(Heap* pHeap) {
    if (pHeap == NULL) {
        printf("pHeap ERROR\n");
        return (FALSE);
    }
    if (pHeap->currentElementCount == 0) {
        return (TRUE);
    }
    return (FALSE);
}

HeapNode* deleteMaxHeapNode(Heap* pHeap) {
    int i;
    int parent;
    int child;
    HeapNode* retNode;
    HeapNode* temp;
    
    if (pHeap == NULL) {
        printf("pHeap ERROR\n");
        return (NULL);
    }
    if (isHeapEmpty(pHeap)) {
        printf("pHeap empty ERROR\n");
        return (NULL);
    }
    retNode = (HeapNode*)malloc(sizeof(HeapNode));
    if (retNode == NULL) {
        printf("retNode ERROR\n");
        return (NULL);
    }
    *retNode = pHeap->pElement[1];
    i = pHeap->currentElementCount;
    temp = &(pHeap->pElement[i]);
    pHeap->currentElementCount--;
    parent = 1;
    child = 2;
    while (child <= pHeap->currentElementCount) {
        if (child < pHeap->currentElementCount && pHeap->pElement[child].data < pHeap->pElement[child + 1].data) {
            child++;
        }
        if (temp->data >= pHeap->pElement[child].data) {
            break ;
        }
        pHeap->pElement[parent] = pHeap->pElement[child]; 
        parent = child;
        child = child * 2;
    }
    pHeap->pElement[parent] = *temp;
    return (retNode);
}

HeapNode* deleteMinHeapNode(Heap* pHeap) {
    int i;
    int parent;
    int child;
    HeapNode* retNode;
    HeapNode* temp;
    
    if (pHeap == NULL) {
        printf("pHeap ERROR\n");
        return (NULL);
    }
    if (isHeapEmpty(pHeap)) {
        printf("pHeap empty ERROR\n");
        return (NULL);
    }
    retNode = (HeapNode*)malloc(sizeof(HeapNode));
    if (retNode == NULL) {
        printf("retNode ERROR\n");
        return (NULL);
    }
    *retNode = pHeap->pElement[1];
    i = pHeap->currentElementCount;
    temp = &(pHeap->pElement[i]);
    pHeap->currentElementCount--;
    parent = 1;
    child = 2;
    while (child <= pHeap->currentElementCount) {
        if (child < pHeap->currentElementCount && pHeap->pElement[child].data > pHeap->pElement[child + 1].data) {
            child++;
        }
        if (temp->data <= pHeap->pElement[child].data) {
            break ;
        }
        pHeap->pElement[parent] = pHeap->pElement[child]; 
        parent = child;
        child = child * 2;
    }
    pHeap->pElement[parent] = *temp;
    return (retNode);
}

void deleteHeap(Heap* pHeap) {
    if (pHeap == NULL) {
        printf("pHeap ERROR\n");
        return ;
    }
    if (pHeap->pElement == NULL) {
        printf("pHeap pElement ERROR\n");
        return ;
    }
    free(pHeap->pElement);
    free(pHeap);
    return ;
}

void displayHeap(Heap* pHeap) {
    if (pHeap == NULL) {
        printf("pHeap ERROR\n");
        return ;
    }
    if (pHeap->pElement == NULL) {
        printf("pHeap pElement ERROR\n");
        return ;
    }
    for (int i = 1; i <= pHeap->currentElementCount; i++) {
        printf("[%d] => data [%d]\n", i, pHeap->pElement[i].data);
    }
}

int main() {
    Heap* pMaxHeap;
    Heap* pMinHeap;
    HeapNode pNode;
    HeapNode* retNode;

    pMaxHeap = createHeap(100);
    pMinHeap = createHeap(100);
    printf("===============================Max Heap===============================\n");
    pNode.data = 15;
    insertMaxHeap(pMaxHeap, pNode);
    pNode.data = 5;
    insertMaxHeap(pMaxHeap, pNode);
    pNode.data = 11;
    insertMaxHeap(pMaxHeap, pNode);
    pNode.data = 1;
    insertMaxHeap(pMaxHeap, pNode);
    pNode.data = 3;
    insertMaxHeap(pMaxHeap, pNode);
    pNode.data = 9;
    insertMaxHeap(pMaxHeap, pNode);
    pNode.data = 7;
    insertMaxHeap(pMaxHeap, pNode);
    displayHeap(pMaxHeap);
    retNode = deleteMaxHeapNode(pMaxHeap);
    printf("returned node data => [%d]\n", retNode->data);
    displayHeap(pMaxHeap);
    retNode = deleteMaxHeapNode(pMaxHeap);
    printf("returned node data => [%d]\n", retNode->data);
    displayHeap(pMaxHeap);
    printf("===============================Min Heap===============================\n");
    pNode.data = 15;
    insertMinHeap(pMinHeap, pNode);
    pNode.data = 5;    
    insertMinHeap(pMinHeap, pNode);
    pNode.data = 11;
    insertMinHeap(pMinHeap, pNode);
    pNode.data = 1;
    insertMinHeap(pMinHeap, pNode);
    pNode.data = 3;
    insertMinHeap(pMinHeap, pNode);
    pNode.data = 9;
    insertMinHeap(pMinHeap, pNode);
    pNode.data = 7;
    insertMinHeap(pMinHeap, pNode);
    displayHeap(pMinHeap);
    retNode = deleteMinHeapNode(pMinHeap);
    printf("returned node data => [%d]\n", retNode->data);
    displayHeap(pMinHeap);
    retNode = deleteMinHeapNode(pMinHeap);
    printf("returned node data => [%d]\n", retNode->data);
   displayHeap(pMinHeap);
   deleteHeap(pMaxHeap);
   deleteHeap(pMinHeap);
}