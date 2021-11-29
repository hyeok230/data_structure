#include "linkedstack.h"
#include <stdio.h>
#include <stdlib.h>

LinkedStack* createLinkedStack() {
    LinkedStack* pStack;
    
    pStack = (LinkedStack*)malloc(sizeof(LinkedStack));
    if (pStack == NULL) {
        printf("malloc ERROR\n");
        return (NULL);
    }
    pStack->currentElementCount = 0;
    pStack->pTopElement = NULL;
    return (pStack);
}

int pushLS(LinkedStack* pStack, StackNode element) {
    StackNode* newNode;
    
    if (pStack == NULL) {
        printf("pStack ERROR\n");
        return (FALSE);
    }
    newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("malloc ERROR\n");
        return (FALSE);
    }
    *newNode = element;
    newNode->pLink = pStack->pTopElement;
    pStack->pTopElement = newNode;
    pStack->currentElementCount++;
    return (TRUE);
}

StackNode* popLS(LinkedStack* pStack) {
    StackNode* retNode;
    
    if (pStack == NULL) {
        printf("pStack ERROR");
        return (NULL);
    }
    if (isLinkedStackEmpty(pStack)) {
        printf("LinkedStack is empty\n");
        return (NULL);
    }
    retNode = pStack->pTopElement;
    pStack->pTopElement = retNode->pLink;
    retNode->pLink = NULL;
    pStack->currentElementCount--;
    return (retNode);
}

StackNode* peekLS(LinkedStack* pStack) {
    if (pStack == NULL) {
        printf("pStack ERROR");
        return (NULL);
    }
    if (isLinkedStackEmpty(pStack)) {
        printf("LinkedStack is empty\n");
        return (NULL);
    }
    return (pStack->pTopElement);
}

void deleteLinkedStack(LinkedStack* pStack) {
    StackNode* delNode;
    int count;

    if (pStack == NULL) {
        printf("pStack ERROR");
        return ;
    }
    count = pStack->currentElementCount;
    for (int i = 0; i < count; i++) {
        delNode = popLS(pStack);
        free(delNode);
    }    
}

int isLinkedStackEmpty(LinkedStack* pStack) {
    if (pStack == NULL) {
        printf("pStack ERROR");
        return (FALSE);
    }
    if (pStack->currentElementCount == 0)
        return (TRUE);
    return (FALSE);
}

void displayLinkedStack(LinkedStack* pStack) {
    StackNode* pNode;
    
    if (pStack == NULL) {
        printf("pStack ERROR");
        return ;
    }
    pNode = pStack->pTopElement;
    for (int i = pStack->currentElementCount - 1; i >= 0; i--) {
        printf("index [%d] => %d\n", i, pNode->data);
        pNode = pNode->pLink;
    }
        
}

int main() {
    LinkedStack* pStack;
    StackNode pNode;
    StackNode* popNode;

    pStack = createLinkedStack();
    pNode.data = 5;
    pNode.pLink = NULL;
    pushLS(pStack, pNode);
    pNode.data = 4;
    pNode.pLink = NULL;
    pushLS(pStack, pNode);
    pNode.data = 3;
    pNode.pLink = NULL;
    pushLS(pStack, pNode);
    pNode.data = 2;
    pNode.pLink = NULL;
    pushLS(pStack, pNode);
    pNode.data = 1;
    pNode.pLink = NULL;
    pushLS(pStack, pNode);
    displayLinkedStack(pStack);
    printf("=================peek & pop=================\n");
    printf("peek => %d\n", peekLS(pStack)->data);
    displayLinkedStack(pStack);
    popNode = popLS(pStack);
    printf("pop => %d\n", popNode->data);
    free(popNode);
    displayLinkedStack(pStack);
    printf("=================peek & pop=================\n");
    printf("peek => %d\n", peekLS(pStack)->data);
    displayLinkedStack(pStack);
    popNode = popLS(pStack);
    printf("pop => %d\n", popNode->data);
    free(popNode);
    displayLinkedStack(pStack);
    printf("=================peek & pop=================\n");
    printf("peek => %d\n", peekLS(pStack)->data);
    displayLinkedStack(pStack);
    popNode = popLS(pStack);
    printf("pop => %d\n", popNode->data);
    free(popNode);
    displayLinkedStack(pStack);
    printf("=================peek & pop=================\n");
    printf("peek => %d\n", peekLS(pStack)->data);
    displayLinkedStack(pStack);
    popNode = popLS(pStack);
    printf("pop => %d\n", popNode->data);
    free(popNode);
    displayLinkedStack(pStack);
    printf("=================peek & pop=================\n");
    printf("peek => %d\n", peekLS(pStack)->data);
    displayLinkedStack(pStack);
    popNode = popLS(pStack);
    printf("pop => %d\n", popNode->data);
    free(popNode);
    displayLinkedStack(pStack);
    printf("===================delete===================\n");
    pNode.data = 5;
    pNode.pLink = NULL;
    pushLS(pStack, pNode);
    pNode.data = 4;
    pNode.pLink = NULL;
    pushLS(pStack, pNode);
    pNode.data = 3;
    pNode.pLink = NULL;
    pushLS(pStack, pNode);
    pNode.data = 2;
    pNode.pLink = NULL;
    pushLS(pStack, pNode);
    pNode.data = 1;
    pNode.pLink = NULL;
    pushLS(pStack, pNode);
    displayLinkedStack(pStack);
    printf("===================delete===================\n");
    deleteLinkedStack(pStack);
    displayLinkedStack(pStack);
}