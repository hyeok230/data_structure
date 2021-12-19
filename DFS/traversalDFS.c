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

void traversalDFS(LinkedGraph* pGraph, int startVertexID) {
    int* vertexVisitCheck;
    LinkedStack* pStack;
    StackNode* pStackNode;
    int vertexID;
    ListNode* pListNode;

    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return ;
    }
    if (startVertexID < 0 || startVertexID >= pGraph->maxVertexCount) {
        printf("startVertexID ERROR\n");
        return ;
    }
    vertexVisitCheck = (int*)malloc(sizeof(int) * getMaxVertexCountLG(pGraph));
    if (vertexVisitCheck == NULL) {
        printf("vertexVisitCheck malloc ERROR\n");
        return ;
    }
    memset(vertexVisitCheck, FALSE, sizeof(int) * getMaxVertexCountLG(pGraph));
    vertexVisitCheck[startVertexID] = TRUE;
    pStack = createLinkedStack();
    if (pushLSForDFS(pStack, startVertexID) == FAIL) {
        printf("push Stack ERROR\n");
        return ;
    }
    while (!isLinkedStackEmpty(pStack)) {
        pStackNode = popLS(pStack);
        if (pStackNode == NULL)
            break;
        vertexID = pStackNode->data;
        printf("visited vertexID => [%d]\n", vertexID);
        pListNode = pGraph->ppAdjEdge[vertexID]->headerNode.pLink;
        while (pListNode) {
            if (vertexVisitCheck[pListNode->vertexID] == FALSE) {
                vertexVisitCheck[pListNode->vertexID] = TRUE;
                if (pushLSForDFS(pStack, pListNode->vertexID) == FAIL) {
                    printf("push Stack ERROR\n");
                    return ;
                }
            }
            pListNode = pListNode->pLink;
        }
        
    }
    free(vertexVisitCheck);
    deleteLinkedStack(pStack);
}

int main() {
    LinkedGraph* undirectedGraph;

    undirectedGraph = createLinkedGraph(8);
    addVertexLG(undirectedGraph, 0);
    addVertexLG(undirectedGraph, 1);
    addVertexLG(undirectedGraph, 2);
    addVertexLG(undirectedGraph, 3);
    addVertexLG(undirectedGraph, 4);
    addVertexLG(undirectedGraph, 5);
    addVertexLG(undirectedGraph, 6);
    addVertexLG(undirectedGraph, 7);
    addEdgeLG(undirectedGraph, 1, 0);
    addEdgeLG(undirectedGraph, 1, 3);
    addEdgeLG(undirectedGraph, 1, 4);
    addEdgeLG(undirectedGraph, 2, 0);
    addEdgeLG(undirectedGraph, 2, 5);
    addEdgeLG(undirectedGraph, 2, 6);
    addEdgeLG(undirectedGraph, 3, 7);
    addEdgeLG(undirectedGraph, 4, 5);
    printf("=========================Undirect Graph=========================\n");
    displayLinkedGraph(undirectedGraph);
    printf("============================== DFS ==============================\n");
    traversalDFS(undirectedGraph, 0);
}