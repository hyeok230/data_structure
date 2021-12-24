#include "floyd.h"
// floyd 알고리즘은 모든 시작노드에서 도착노드의 최단거리를 구한다.

int** floyd(LinkedGraph* pGraph) {
    int** retList;
    int maxVertexCount;

    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (NULL);
    }
    maxVertexCount = pGraph->maxVertexCount;
    retList = (int**)malloc(sizeof(int*) * maxVertexCount);
    if (retList == NULL) {
        printf("retList malloc ERROR\n");
        return (NULL);
    }
    for (int i = 0; i < maxVertexCount; i++) {
        retList[i] = (int*)malloc(sizeof(int) * maxVertexCount);
        if (retList[i] == NULL) {
            for (int j = 0; j < i -1; j++) {
                if (retList[j] != NULL) {
                    free(retList[j]);
                }
            }
            if (retList != NULL) {
                free(retList);
            }
            printf("retList[%d] malloc ERROR\n", i);
            return (NULL);
        }
    }
    for (int i = 0; i < maxVertexCount; i++) {
        for (int j = 0; j < maxVertexCount; j++) {
            if (i == j) {
                retList[i][j] = 0;
            } else {
                retList[i][j] = getEdgeWeight(pGraph, i, j);
            }
        }
    }
    for (int v = 0; v < maxVertexCount; v++) { // v는 중간노드
        for (int r = 0; r < maxVertexCount; r++) { // r은 시작노드
            for (int s = 0; s < maxVertexCount; s++) { // s는 종료노드
                if (retList[r][v] + retList[v][s] < retList[r][s]) {
                    retList[r][s] = retList[r][v] + retList[v][s];
                }
            }
        }
    }
    for (int i = 0; i < maxVertexCount; i++) {
        for (int j = 0; j < maxVertexCount; j++) {
            printf("(%d, %d) => %d\n", i, j, retList[i][j]);
        }
        printf("==================================\n");
    }
    return (retList);
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
        return (FAIL);
    }
}

int main() {
    LinkedGraph* pGraph;
    int** spList;

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
    printf("============================floyd=============================\n");
    spList = floyd(pGraph);
}