#include "kruskal2.h"

LinkedGraph* mstKruskal(LinkedGraph* pGraph) {
    Heap*   orderedHeap;
    HeapNode* pHeapNode;
    LinkedGraph* mstGraph;
    int* vertexUnion;

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
    vertexUnion = (int*)malloc(sizeof(int) * pGraph->maxVertexCount);
    if (vertexUnion == NULL) {
        printf("vertexUinon malloc ERROR\n");
        return (NULL);
    }
    for (int i = 0; i < pGraph->maxVertexCount; i++) {
        vertexUnion[i] = i;
    }
    for (int i = 0; i < pGraph->currentEdgeCount; i++) {
        pHeapNode = deleteMinHeapNode(orderedHeap);
        if (pHeapNode) {
            if (checkCycle(vertexUnion, pHeapNode->fromVertexID, pHeapNode->toVertexID) == FALSE) {
                unionParent(vertexUnion, pHeapNode->fromVertexID, pHeapNode->toVertexID);
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

void unionParent(int* vertexUnion, int fromVertexID, int toVertexID) {
    fromVertexID = getParent(vertexUnion, fromVertexID);
    toVertexID = getParent(vertexUnion, toVertexID);
    if (fromVertexID < toVertexID) {
        vertexUnion[toVertexID] = fromVertexID;
    } else {
        vertexUnion[fromVertexID] = toVertexID;
    }
}

int getParent(int* vertexUnion, int vertexID) {
    if (vertexUnion[vertexID] == vertexID) {
        return (vertexID);
    }
    return (getParent(vertexUnion, vertexUnion[vertexID]));
}

int checkCycle(int* vertexUnion, int fromVertexID, int toVertexID) {
    int parentForFromVertexID;
    int parentForToVertexID;
    
    parentForFromVertexID = getParent(vertexUnion, fromVertexID);
    parentForToVertexID = getParent(vertexUnion, toVertexID);
    if (parentForFromVertexID == parentForToVertexID) {
        return (TRUE);
    }
    return (FALSE);
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
