#include "kruskal.h"
#include <stdio.h>
#include <stdlib.h>

LinkedGraph* mstKruskal(LinkedGraph* pGraph) {
    Heap*   orderedHeap;
    HeapNode* pHeapNode;
    LinkedGraph* mstGraph;

    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (NULL);
    }
    orderedHeap = orderEdges(pGraph);
    if (pGraph->graphType == GRAPH_UNDIRECTED) {
        mstGraph = createLinkedGraph(pGraph->maxVertexCount);
    } else {
        mstGraph = createLinkedDirectedGraph(pGraph->maxVertexCount);
    }
    for (int i = 0; i < pGraph->currentEdgeCount; i++) {
        pHeapNode = deleteMinHeapNode(orderedHeap);
        if (pHeapNode) {
            if (checkCycle(mstGraph, pHeapNode->fromVertexID, pHeapNode->toVertexID) == FALSE) {
                if (checkVertexValid(mstGraph, pHeapNode->fromVertexID) == FALSE) {
                    addVertexLG(mstGraph, pHeapNode->fromVertexID);
                }
                if (checkVertexValid(mstGraph, pHeapNode->toVertexID) == FALSE) {
                    addVertexLG(mstGraph, pHeapNode->toVertexID);
                }
                addEdgewithWeightLG(mstGraph, pHeapNode->fromVertexID, pHeapNode->toVertexID, pHeapNode->weight);
                printf("Edge [%d, %d] -> Weight [%d]\n", pHeapNode->fromVertexID, pHeapNode->toVertexID, pHeapNode->weight);
            }
        }
        free(pHeapNode);
        if (mstGraph->currentVertexCount == pGraph->currentVertexCount) {
            break;
        }
    }
    return (mstGraph);
}

Heap* orderEdges(LinkedGraph* pGraph) {
    Heap* retHeap;
    HeapNode element;
    LinkedList* pList;
    ListNode* pNode;
    
    retHeap = createHeap(pGraph->currentEdgeCount);
    if (retHeap == NULL) {
        printf("create Heap ERROR\n");
        return (NULL);
    }
    pList = NULL;
    pNode = NULL;
    for (int i = 0; i < pGraph->maxVertexCount; i++) {
        if (checkVertexValid(pGraph, i) == TRUE) {
            pList = pGraph->ppAdjEdge[i];
            pNode = pList->headerNode.pLink;
        }
        while (pNode) {
            if ((pGraph->graphType == GRAPH_DIRECTED) || (pGraph->graphType == GRAPH_UNDIRECTED && i < pNode->vertexID)) {
                element.fromVertexID = i;
                element.toVertexID = pNode->vertexID;
                element.weight = pNode->weight;
                insertMinHeap(retHeap, element);
            }
            pNode = pNode->pLink;
        }
    }
    return (retHeap);
}

// DFS를 활용한 cycle search, 노드를 추가하기 전에 from에서 to로 갈 방법이 없어야 한다.
int checkCycle(LinkedGraph* pGraph, int fromVertexID, int toVertexID) {
    int result;
    
    result = traversalDFS(pGraph, fromVertexID, toVertexID);
    return (result);
}

int main() {
    LinkedGraph* pGraph;
    LinkedGraph* mstGraph;

    pGraph = createLinkedGraph(6);
    addVertexLG(pGraph, 0);
    addVertexLG(pGraph, 1);
    addVertexLG(pGraph, 2);
    addVertexLG(pGraph, 3);
    addVertexLG(pGraph, 4);
    addVertexLG(pGraph, 5);
    addEdgewithWeightLG(pGraph, 0, 1, 4);
    addEdgewithWeightLG(pGraph, 0, 2, 3);
    addEdgewithWeightLG(pGraph, 1, 2, 2);
    addEdgewithWeightLG(pGraph, 2, 3, 1);
    addEdgewithWeightLG(pGraph, 3, 4, 1);
    addEdgewithWeightLG(pGraph, 4, 5, 6);
    addEdgewithWeightLG(pGraph, 3, 5, 5);
    printf("============================Graph=============================\n");
    displayLinkedGraph(pGraph);
    printf("===========================mstGraph============================\n");
    mstGraph = mstKruskal(pGraph);
    displayLinkedGraph(mstGraph);
}