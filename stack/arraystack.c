#include "arraystack.h"
#include <stdio.h>
#include <stdlib.h>

ArrayStack* createArrayStack(int maxElementCount) {
    ArrayStack* pStack;
    
    if (maxElementCount <= 0) {
        printf("maxElementCount ERROR\n");
        return (NULL);
    }
    pStack = (ArrayStack*)malloc(sizeof(ArrayStack));
    if (pStack == NULL) {
        printf("malloc ERROR\n");
        return (NULL);
    }
    pStack->maxElementCount = maxElementCount;
    pStack->currentElementCount = 0;
    pStack->pElement = (ArrayStackNode*)malloc(sizeof(ArrayStackNode) * maxElementCount);
    if (pStack->pElement == NULL) {
        printf("malloc ERROR\n");
        return (NULL);
    }   
    return (pStack);
}

int pushAS(ArrayStack* pStack, ArrayStackNode element) {    
    if (pStack == NULL) {
        printf("pStack ERROR\n");
        return (FALSE);
    }
    //Overflow Check
    if (isArrayStackFull(pStack)) {
        printf("pStack is full\n");
        return (FALSE);
    }
    pStack->pElement[pStack->currentElementCount] = element;
    pStack->currentElementCount++;
    return (TRUE);
}

ArrayStackNode* popAS(ArrayStack* pStack) {
    ArrayStackNode* retNode;
    
    if (pStack == NULL) {
        printf("pStack ERROR\n");
        return (NULL);
    }
    //Underflow check
    if (isArrayStackEmpty(pStack)) {
        printf("pStack is Empty");
        return (NULL);
    }
    retNode = &(pStack->pElement[pStack->currentElementCount - 1]);
    pStack->currentElementCount--;
    return (retNode);
}

ArrayStackNode* peekAS(ArrayStack* pStack) {
    ArrayStackNode* retNode;
    
    if (pStack == NULL) {
        printf("pStack ERROR\n");
        return (NULL);
    }
    retNode = &(pStack->pElement[pStack->currentElementCount - 1]);
    return (retNode);
}

void deleteArrayStack(ArrayStack* pStack) {
    if (pStack == NULL) {
        printf("pStack ERROR\n");
        return ;
    }
    if (pStack->pElement != NULL)
        free(pStack->pElement);
    pStack->currentElementCount = 0;
}

int isArrayStackFull(ArrayStack* pStack) {
    if (pStack == NULL) {
        printf("pStack ERROR\n");
        return (FALSE);
    }
    if (pStack->currentElementCount == pStack->maxElementCount)
        return (TRUE);
    return (FALSE);
}

int isArrayStackEmpty(ArrayStack* pStack) {
    if (pStack == NULL) {
        printf("pStack ERROR\n");
        return (FALSE);
    }
    if (pStack->currentElementCount == 0)
        return (TRUE);
    return (FALSE);
}

void displayStack(ArrayStack* pStack) {
    if (pStack == NULL) {
        printf("pStack ERROR\n");
        return ;
    }
    for (int i = pStack->currentElementCount - 1; i >= 0; i--) {
        printf("index [%d] => %d\n", i, pStack->pElement[i].data);
    }    
}

int main() {
    ArrayStack* pStack;
    ArrayStackNode pNode;

    pStack = createArrayStack(5);
    pNode.data = 5;
    pushAS(pStack, pNode);
    pNode.data = 4;
    pushAS(pStack, pNode);
    pNode.data = 3;
    pushAS(pStack, pNode);
    pNode.data = 2;
    pushAS(pStack, pNode);
    pNode.data = 1;
    pushAS(pStack, pNode);
    displayStack(pStack);
    printf("=================peek & pop=================\n");
    printf("peek => %d\n", peekAS(pStack)->data);
    displayStack(pStack);
    printf("pop => %d\n", popAS(pStack)->data);
    displayStack(pStack);
    printf("=================peek & pop=================\n");
    printf("peek => %d\n", peekAS(pStack)->data);
    displayStack(pStack);
    printf("pop => %d\n", popAS(pStack)->data);
    displayStack(pStack);
    printf("=================peek & pop=================\n");
    printf("peek => %d\n", peekAS(pStack)->data);
    displayStack(pStack);
    printf("pop => %d\n", popAS(pStack)->data);
    displayStack(pStack);
    printf("=================peek & pop=================\n");
    printf("peek => %d\n", peekAS(pStack)->data);
    displayStack(pStack);
    printf("pop => %d\n", popAS(pStack)->data);
    displayStack(pStack);
    printf("=================peek & pop=================\n");
    printf("peek => %d\n", peekAS(pStack)->data);
    displayStack(pStack);
    printf("pop => %d\n", popAS(pStack)->data);
    displayStack(pStack);
    printf("===================delete===================\n");
    pNode.data = 5;
    pushAS(pStack, pNode);
    pNode.data = 4;
    pushAS(pStack, pNode);
    pNode.data = 3;
    pushAS(pStack, pNode);
    pNode.data = 2;
    pushAS(pStack, pNode);
    pNode.data = 1;
    pushAS(pStack, pNode);
    displayStack(pStack);
    printf("===================delete===================\n");
    deleteArrayStack(pStack);
    displayStack(pStack);
}
