#include "traversalBFS.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int enqueueLQForBFS(LinkedDeque* pQueue, int nodeID) {
    DequeNode pNode;

    pNode.data = nodeID;
    pNode.pLLink = NULL;
    pNode.pRLink = NULL;
    if (insertRearLD(pQueue, pNode) == FALSE) {
        return (FAIL);
    }
    return (SUCCESS);
}

void traversalBFS(LinkedGraph* pGraph, int startVertexID) {
    int* vertexVisitCheck;
    LinkedDeque* pQueue;
    DequeNode* pQueueNode;
    int vertexID;
    ListNode* pListNode;

    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return ;
    }
    if (startVertexID < 0 || startVertexID >= getMaxVertexCountLG(pGraph)) {
        printf("startvertexID ERROR\n");
        return ;
    }
    vertexVisitCheck = (int*)malloc(sizeof(int) * getMaxVertexCountLG(pGraph));
    if (vertexVisitCheck == NULL) {
        printf("vertexVisitCheck malloc ERROR\n");
        return ;
    }
    memset(vertexVisitCheck, FALSE, sizeof(int) * getMaxVertexCountLG(pGraph));
    vertexVisitCheck[startVertexID] = TRUE;
    pQueue = createLinkedDeque();
    if (enqueueLQForBFS(pQueue, startVertexID) == FAIL) {
        printf("Enqueue ERROR\n");
        return ;
    }
    while (!isLinkedDequeEmpty(pQueue)) {
        pQueueNode = deleteFrontLD(pQueue);
        vertexID = pQueueNode->data;
        printf("visited vertexID => [%d]\n", vertexID);
        pListNode = pGraph->ppAdjEdge[vertexID]->headerNode.pLink;
        while(pListNode) {
            if (vertexVisitCheck[pListNode->vertexID] == FALSE) {
                vertexVisitCheck[pListNode->vertexID] = TRUE;
                if (enqueueLQForBFS(pQueue, pListNode->vertexID) == FAIL) {
                    printf("Enqueue ERROR\n");
                    return ;
                }
            }
            pListNode = pListNode->pLink;
        }
    }
    free(vertexVisitCheck);
    deleteLinkedDeque(pQueue);
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
    traversalBFS(undirectedGraph, 0);
}