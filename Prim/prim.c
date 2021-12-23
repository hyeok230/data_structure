#include "prim.h"

void printVertexUnion(int* vertexUnion) {
    for (int i = 0; i < 6; i++) {
        printf("%d => %d\n", i, vertexUnion[i]);
    }
}

LinkedGraph* mstPrim(LinkedGraph* pGraph, int startVertexID) {
    LinkedGraph* mstGraph;
    GraphEdge minWeightEdge;
    int* vertexUnion;
    int fromVertexID;

    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (NULL);
    }
    if (pGraph->graphType == GRAPH_UNDIRECTED) {
        mstGraph = createLinkedGraph(pGraph->maxVertexCount);
    } else {
        mstGraph = createLinkedDirectedGraph(pGraph->maxVertexCount);
    }
    if (mstGraph == NULL) {
        return (NULL);
    }
    vertexUnion = (int*)malloc(sizeof(int) * pGraph->maxVertexCount);
    if (vertexUnion == NULL) {
        printf("vertexUinon malloc ERROR\n");
        return (NULL);
    }
    for (int i = 0; i < pGraph->maxVertexCount; i++) {
        vertexUnion[i] = i;
    }
    addVertexLG(mstGraph, startVertexID);
    while (mstGraph->currentVertexCount < pGraph->currentVertexCount) {
        minWeightEdge.fromVertexID = 0;
        minWeightEdge.toVertexID = 0;
        minWeightEdge.weight = MAX_INT;
        for (int i = 0; i < mstGraph->maxVertexCount; i++) {
            if (mstGraph->pVertex[i] == USED) {
                fromVertexID = i;
                getMinWeightEdge(pGraph, mstGraph, fromVertexID, &minWeightEdge, vertexUnion);
            }
        }
        addVertexLG(mstGraph, minWeightEdge.toVertexID);
        addEdgewithWeightLG(mstGraph, minWeightEdge.fromVertexID, minWeightEdge.toVertexID, minWeightEdge.weight);
        unionParent(vertexUnion, minWeightEdge.fromVertexID, minWeightEdge.toVertexID);
    }
    return (mstGraph);
}

void getMinWeightEdge(LinkedGraph* pGraph, LinkedGraph* mstGraph, int fromVertexID, GraphEdge* minWeightEdge, int* vertexUnion) {
    ListNode* pNode;

    pNode = pGraph->ppAdjEdge[fromVertexID]->headerNode.pLink;
    while (pNode) {
        if (pNode->weight < minWeightEdge->weight) {
            if (checkEdgeExist(mstGraph, fromVertexID, pNode->vertexID) == FALSE) {
                if (checkCycle(vertexUnion, fromVertexID, pNode->vertexID) == FALSE) {
                    minWeightEdge->fromVertexID = fromVertexID;
                    minWeightEdge->toVertexID = pNode->vertexID;
                    minWeightEdge->weight = pNode->weight;
                }
            }
        }
        pNode = pNode->pLink;
    }
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
    return (vertexUnion[vertexID] = getParent(vertexUnion, vertexUnion[vertexID]));
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
    mstGraph = mstPrim(pGraph, 0);
    displayLinkedGraph(mstGraph);
}