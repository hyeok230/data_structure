#include "dijkstra.h"

int* dijkstra(LinkedGraph* pGraph, int startVertexID) {
    int* retList; // startVertexID 에서 각 노드에 도달하는 최단 거리
    int* selectVertexID; // 계산해야할 노드들이 담겨져 있음
    int vertexID;
    int toVertexID;
    int weight;
    int y_v;
    int y_w;
    ListNode* pNode;

    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (NULL);
    }
    retList = (int*)malloc(sizeof(int) * pGraph->maxVertexCount);
    selectVertexID = (int*)malloc(sizeof(int) * pGraph->maxVertexCount);
    if (retList == NULL || selectVertexID == NULL) {
        printf("List malloc ERROR\n");
        return (NULL);
    }
    for (int i = 0; i < pGraph->maxVertexCount; i++) {
        if (i == startVertexID) {
            retList[i] = FALSE;
        } else {
            if (pGraph->pVertex[i] == USED) {
                retList[i] = getEdgeWeight(pGraph, startVertexID, i);
                selectVertexID[i] = TRUE;
            } else {
                retList[i] = MAX_INT;
                selectVertexID[i] = FALSE;
            }
        }
    }
    for (int i =0; i < pGraph->currentVertexCount - 1; i++) {
        // 현재 계산된 거리 중에서 가장 가깝고, 방문되지 않은 ID를 찾는다.
        vertexID = getClosestVertexID(retList, selectVertexID, pGraph->maxVertexCount);
        selectVertexID[vertexID] = FALSE;

        pNode = pGraph->ppAdjEdge[vertexID]->headerNode.pLink;
        while (pNode) {
            toVertexID = pNode->vertexID;
            weight = pNode->weight; // Cvw
            // y_v + Cvw 와 y_w 중 작은 값으로 업데이트 
            y_v = retList[vertexID];
            y_w = retList[toVertexID];
            if (y_v + weight < y_w) {
                retList[toVertexID] = y_v + weight;
            }
            pNode = pNode->pLink;
        }

    }
    for (int i = 0; i < pGraph->maxVertexCount; i++) {
        printf("(%d, %d) => %d\n", startVertexID, i, retList[i]);
    }
    free(selectVertexID);
    return (retList);
}

int getClosestVertexID(int* retList, int* selectVertexID, int maxVertexCount) {
    int vertexID;
    int weight;

    vertexID = 0;
    weight = MAX_INT;
    for (int i = 0; i < maxVertexCount; i++) {
        if (selectVertexID[i] == TRUE) {
            if (retList[i] < weight) {
                weight = retList[i];
                vertexID = i;
            }
        }
    }
    return (vertexID);
}

int getEdgeWeight(LinkedGraph* pGraph, int fromVertexID, int toVertexID) {
    ListNode* pNode;
    
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (FAIL);
    }
    if (pGraph->pVertex[fromVertexID] == USED && pGraph->pVertex[toVertexID] == USED) {
        if (checkEdgeExist(pGraph, fromVertexID, toVertexID) == TRUE) {
            pNode = pGraph->ppAdjEdge[fromVertexID]->headerNode.pLink;
            while (pNode) {
                if (pNode->vertexID == toVertexID) {
                    return (pNode->weight);
                }
                pNode = pNode->pLink;
            }
            return (FAIL);
        } else {
            return (MAX_INT);
        }
    } else {
        printf("vertex not used ERROR\n");
        return (FAIL);
    }
}

int main() {
    LinkedGraph* pGraph;
    int* spList;

    pGraph = createLinkedGraph(6);
    addVertexLG(pGraph, 0);
    addVertexLG(pGraph, 1);
    addVertexLG(pGraph, 2);
    addVertexLG(pGraph, 3);
    addVertexLG(pGraph, 4);
    addVertexLG(pGraph, 5);
    addEdgewithWeightLG(pGraph, 0, 1, 1);
    addEdgewithWeightLG(pGraph, 0, 2, 4);
    addEdgewithWeightLG(pGraph, 1, 2, 2);
    addEdgewithWeightLG(pGraph, 2, 3, 1);
    addEdgewithWeightLG(pGraph, 3, 4, 8);
    addEdgewithWeightLG(pGraph, 4, 5, 4);
    addEdgewithWeightLG(pGraph, 3, 5, 3);
    printf("============================Graph=============================\n");
    displayLinkedGraph(pGraph);
    printf("===========================dijkstra============================\n");
    spList = dijkstra(pGraph, 0);
}