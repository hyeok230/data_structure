#include "linkedgraph.h"
#include "linkedstack.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int pushLSForDFS(LinkedStack* pStack, int nodeID) {
    StackNode pNode;

    pNode.data = nodeID;
    pNode.pLink = NULL;
    if (pushLS(pStack, pNode) == TRUE) {
        return (SUCCESS);
    }
    return (FAIL);
}

int traversalDFS(LinkedGraph* pGraph, int startVertexID, int toVertexID) {
    int* vertexVisitCheck;
    LinkedStack* pStack;
    StackNode* pStackNode;
    int vertexID;
    ListNode* pListNode;
    int result;

    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (TRUE);
    }
    if (startVertexID < 0 || startVertexID >= pGraph->maxVertexCount) {
        printf("startVertexID ERROR\n");
        return (TRUE);
    }
    vertexVisitCheck = (int*)malloc(sizeof(int) * getMaxVertexCountLG(pGraph));
    if (vertexVisitCheck == NULL) {
        printf("vertexVisitCheck malloc ERROR\n");
        return (TRUE);
    }
    memset(vertexVisitCheck, FALSE, sizeof(int) * getMaxVertexCountLG(pGraph));
    vertexVisitCheck[startVertexID] = TRUE;
    pStack = createLinkedStack();
    if (pushLSForDFS(pStack, startVertexID) == FAIL) {
        printf("push Stack ERROR\n");
        return (TRUE);
    }
    result = TRUE;
    while (!isLinkedStackEmpty(pStack)) {
        pStackNode = popLS(pStack);
        if (pStackNode == NULL)
            break;
        vertexID = pStackNode->data;
        if (vertexID == toVertexID) {
            result = FALSE;
        }
        pListNode = pGraph->ppAdjEdge[vertexID]->headerNode.pLink;
        while (pListNode) {
            if (vertexVisitCheck[pListNode->vertexID] == FALSE) {
                vertexVisitCheck[pListNode->vertexID] = TRUE;
                if (pushLSForDFS(pStack, pListNode->vertexID) == FAIL) {
                    printf("push Stack ERROR\n");
                    return (TRUE);
                }
            }
            pListNode = pListNode->pLink;
        }
        
    }
    free(vertexVisitCheck);
    deleteLinkedStack(pStack);
    return (result);
}