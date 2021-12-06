#include "arrayqueue.h"
#include <stdio.h>
#include <stdlib.h>

ArrayQueue* createArrayQueue(int maxElementCount) {
    ArrayQueue* pQueue;
    
    if (maxElementCount <= 0) {
        printf("maxElementCount Error\n");
        return (NULL);
    }
    pQueue = (ArrayQueue*)malloc(sizeof(ArrayQueue));
    if (pQueue == NULL) {
        printf("malloc Error\n");
        return (NULL);
    }
    pQueue->maxElementCount = maxElementCount;
    pQueue->currentElementCount = 0;
    pQueue->front = -1;
    pQueue->rear = -1;
    pQueue->pElement = (ArrayQueueNode*)malloc(sizeof(ArrayQueueNode) * maxElementCount);
    if (pQueue->pElement == NULL) {
        printf("malloc Error\n");
        return (NULL);
    }
    return (pQueue);
}

int enqueueAQ(ArrayQueue* pQueue, ArrayQueueNode element) {
    if (pQueue == NULL) {
        printf("pQueue Error\n");
        return (FALSE);
    }
    if (isArrayQueueFull(pQueue)) {
        printf("pQueue full Error\n");
        return (FALSE);
    }
    pQueue->rear = (pQueue->rear + 1) % (pQueue->maxElementCount);
    pQueue->pElement[pQueue->rear] = element;
    pQueue->currentElementCount++;
    return (TRUE);
}

ArrayQueueNode *dequeueAQ(ArrayQueue* pQueue) {
    ArrayQueueNode* retNode;

    if (pQueue == NULL) {
        printf("pQueue Error\n");
        return (NULL);
    }
    if (isArrayQueueEmpty(pQueue)) {
        printf("pQueue empty Error\n");
        return (NULL);
    }
    pQueue->front = (pQueue->front + 1) % pQueue->maxElementCount;
    retNode = &(pQueue->pElement[pQueue->front]); 
    pQueue->currentElementCount--;
    return (retNode);
}

ArrayQueueNode *peekAQ(ArrayQueue* pQueue) {
    ArrayQueueNode* retNode;
    
    if (pQueue == NULL) {
        printf("pQueue Error\n");
        return (NULL);
    }
    if (isArrayQueueEmpty(pQueue)) {
        printf("pQueue empty Error\n");
        return (NULL);
    }
    retNode = &(pQueue->pElement[(pQueue->front + 1) % (pQueue->maxElementCount)]);
    return (retNode);
}

void deleteArrayQueue(ArrayQueue* pQueue) {
    
    if (pQueue == NULL) {
        printf("pQueue Error\n");
        return ;
    }
    free(pQueue->pElement);
    pQueue->currentElementCount = 0;
    pQueue->front = -1;
    pQueue->rear = -1;
}

int isArrayQueueFull(ArrayQueue* pQueue) {
    if (pQueue == NULL) {
        printf("pQueue Error\n");
        return (FALSE);
    }
    if (pQueue->currentElementCount == pQueue->maxElementCount) {
        return (TRUE);
    }
    return (FALSE);
}

int isArrayQueueEmpty(ArrayQueue* pQueue) {
    if (pQueue == NULL) {
        printf("pQueue Error\n");
        return (FALSE);
    }
    if (pQueue->currentElementCount == 0) {
        return (TRUE);
    }
    return (FALSE);
}

void displayQueue(ArrayQueue* pQueue) {
    if (pQueue == NULL) {
        printf("pQueue Error\n");
        return ;
    }
    for (int i = pQueue->rear; i > pQueue->front; i--) {
        printf("data [%d]\n", pQueue->pElement[i].data);
    }
}

int main() {
    ArrayQueue* pQueue;
    ArrayQueueNode element;
    ArrayQueueNode* retNode;

    pQueue = createArrayQueue(10);
    element.data = 1;
    enqueueAQ(pQueue, element);
    element.data = 2;
    enqueueAQ(pQueue, element);
    element.data = 3;
    enqueueAQ(pQueue, element);
    element.data = 4;
    enqueueAQ(pQueue, element);
    displayQueue(pQueue);
    printf("==============================================\n");
    retNode = peekAQ(pQueue);
    printf("peekAQ => data [%d]\n", retNode->data);
    retNode = dequeueAQ(pQueue);
    printf("dequeueAQ => data [%d]\n", retNode->data);
    displayQueue(pQueue);
    printf("===============deleteArrayQueue==============\n");
    deleteArrayQueue(pQueue);
    displayQueue(pQueue);
}