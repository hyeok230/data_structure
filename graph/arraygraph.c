#include "arraygraph.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

ArrayGraph* createArrayGraph(int maxVertexCount) {
    ArrayGraph* pGraph;

    if (maxVertexCount <= 0) {
        printf("maxVertexCount ERROR\n");
        return (NULL);
    }
    pGraph = (ArrayGraph*)malloc(sizeof(ArrayGraph));
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (NULL);
    }
    pGraph->maxVertexCount = maxVertexCount;
    pGraph->currentVertexCount = 0;
    pGraph->graphType = GRAPH_UNDIRECTED;
    // 노드의 사용 여부를 저장하는 배열 메모리 할당
    pGraph->pVertex = (int*)malloc(sizeof(int) * maxVertexCount);
    if (pGraph->pVertex == NULL) {
        printf("pVertex malloc ERROR\n");
        return (NULL);
    }
    memset(pGraph->pVertex, NOT_USED, sizeof(int) * maxVertexCount);
    // 간선을 저장하는 배열의 메모리 할당
    pGraph->ppAdjEdge = (int**)malloc(sizeof(int*) * maxVertexCount);
    if (pGraph->ppAdjEdge == NULL) {
        printf("ppAdjEdge malloc ERROR\n");
        return (NULL);
    }
    for (int i = 0; i < maxVertexCount; i++) {
        pGraph->ppAdjEdge[i] = (int*)malloc(sizeof(int) * maxVertexCount);
        if (pGraph->ppAdjEdge[i] == NULL) {
            printf("ppAdjEdge[%d] malloc ERROR\n", i);
            return (NULL);
        }
    }
    for (int i = 0; i < maxVertexCount; i++) {
        memset(pGraph->ppAdjEdge[i], 0, sizeof(int) * maxVertexCount);
    }
    return (pGraph);
}

ArrayGraph* createArrayDirectedGraph(int maxVertexCount) {
    ArrayGraph* pGraph;

     pGraph = createArrayGraph(maxVertexCount);
     pGraph->graphType = GRAPH_DIRECTED;
     return (pGraph);
}

void deleteArrayGraph(ArrayGraph* pGraph) {
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return ;
    }
    for (int i = 0; i < pGraph->maxVertexCount; i++) {
        free(pGraph->ppAdjEdge[i]);
    }
    free(pGraph->ppAdjEdge);
    free(pGraph->pVertex);
    free(pGraph);
}

int isEmptyAG(ArrayGraph* pGraph) {
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (FALSE);
    }
    if (pGraph->currentVertexCount == 0)
        return (TRUE);
    return (FALSE);
}

int addVertexAG(ArrayGraph* pGraph, int vertexID) {
    int i;
    
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (FAIL);
    }
    if (vertexID > pGraph->maxVertexCount) {
        printf("vertexID ERROR\n");
        return (FAIL);
    }
    if (pGraph->pVertex[vertexID] == USED) {
        printf("vertexID already used\n");
        return (FAIL);
    }
    pGraph->currentVertexCount++;
    pGraph->pVertex[vertexID] = USED;
    return (SUCCESS);
}

int addEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID) {
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (FALSE);
    }
    addEdgewithWeightAG(pGraph, fromVertexID, toVertexID, 1);
}

int addEdgewithWeightAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID, int weight) {
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (FAIL);
    }
    if (checkVertexValid(pGraph, fromVertexID) == FALSE || checkVertexValid(pGraph, toVertexID) == FALSE) {
        printf("Vertex not used ERROR\n");
        return (FAIL);
    }
    if (pGraph->ppAdjEdge[fromVertexID][toVertexID] == 0) {
        pGraph->ppAdjEdge[fromVertexID][toVertexID] = weight;
        if (pGraph->graphType == GRAPH_UNDIRECTED) {
            pGraph->ppAdjEdge[toVertexID][fromVertexID] = weight;
        }
    } else {
        printf("Edge already exist\n");
        return (FAIL);
    }
}

int checkVertexValid(ArrayGraph* pGraph, int vertexID) {
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (FAIL);
    }
    if (pGraph->pVertex[vertexID] == USED) {
        return (TRUE);
    }
    return (FALSE);
}

int removeVertexAG(ArrayGraph* pGraph, int vertexID) {
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (FAIL);
    }
    if (pGraph->pVertex[vertexID] == NOT_USED) {
        printf("Vertex already not used\n");
        return (FAIL);
    }
    pGraph->pVertex[vertexID] = NOT_USED;
    for (int i = 0; i < pGraph->maxVertexCount; i++) {
        pGraph->ppAdjEdge[vertexID][i] = 0;
        pGraph->ppAdjEdge[i][vertexID] = 0;
    }
    pGraph->currentVertexCount--;
    return (SUCCESS);
}

int removeEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID) {
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (FAIL);
    }
    if (checkVertexValid(pGraph, fromVertexID) == FALSE || checkVertexValid(pGraph, toVertexID) == FALSE) {
        printf("Vertex not used ERROR\n");
        return (FAIL);
    }
    if (pGraph->ppAdjEdge[fromVertexID][toVertexID] != 0) {
        pGraph->ppAdjEdge[fromVertexID][toVertexID] = 0;
        if (pGraph->graphType == GRAPH_UNDIRECTED) {
            pGraph->ppAdjEdge[toVertexID][fromVertexID] = 0;
        }
    } else {
        printf("Edge does not exist\n");
        return (FAIL);
    }
    return (TRUE);
}

void displayArrayGraph(ArrayGraph* pGraph) {
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return ;
    }
    printf("==========================Vertex Used==========================\n");
    for (int i = 0; i < pGraph->maxVertexCount; i++) {
        printf("vertexID => [%d] ", i);
        if (pGraph->pVertex[i] == USED) {
            printf("USED\n");
        } else {
            printf("NOT USED\n");
        }
    }
    printf("=============================Edge=============================\n");
    for (int i = 0; i < pGraph->maxVertexCount; i++) {
        for (int j = 0; j < pGraph->maxVertexCount; j++) {
            printf("%d ", pGraph->ppAdjEdge[i][j]);
        }
        printf("\n");
    }
}

int main() {
    ArrayGraph* undirectGraph;
    ArrayGraph* directGraph;

    undirectGraph = createArrayGraph(6);
    directGraph = createArrayDirectedGraph(6);
    addVertexAG(undirectGraph, 0);
    addVertexAG(undirectGraph, 1);
    addVertexAG(undirectGraph, 2);
    addVertexAG(undirectGraph, 3);
    addVertexAG(undirectGraph, 4);
    addVertexAG(undirectGraph, 5);
    addEdgeAG(undirectGraph, 1, 0);
    addEdgeAG(undirectGraph, 2, 0);
    addEdgeAG(undirectGraph, 2, 1);
    addEdgeAG(undirectGraph, 3, 2);
    addEdgeAG(undirectGraph, 4, 3);
    addEdgeAG(undirectGraph, 5, 3);
    addEdgeAG(undirectGraph, 5, 4);
    printf("=========================Undirect Graph=========================\n");
    displayArrayGraph(undirectGraph);
    printf("=======================remove vertexID 1=======================\n");
    removeVertexAG(undirectGraph, 1);
    displayArrayGraph(undirectGraph);
    printf("====================remove edge (2,0) (0,2)====================\n");
    removeEdgeAG(undirectGraph, 2, 0);
    displayArrayGraph(undirectGraph);
    addVertexAG(directGraph, 0);
    addVertexAG(directGraph, 1);
    addVertexAG(directGraph, 2);
    addVertexAG(directGraph, 3);
    addVertexAG(directGraph, 4);
    addVertexAG(directGraph, 5);
    addEdgewithWeightAG(directGraph, 0, 1, 4);
    addEdgewithWeightAG(directGraph, 1, 2, 1);
    addEdgewithWeightAG(directGraph, 2, 0, 2);
    addEdgewithWeightAG(directGraph, 2, 1, 3);
    addEdgewithWeightAG(directGraph, 2, 3, 2);
    addEdgewithWeightAG(directGraph, 3, 2, 1);
    addEdgewithWeightAG(directGraph, 3, 4, 1);
    addEdgewithWeightAG(directGraph, 4, 5, 1);
    addEdgewithWeightAG(directGraph, 5, 3, 2);
    printf("==========================Direct Graph===========================\n");
    displayArrayGraph(directGraph);
    printf("=======================remove vertexID 1=======================\n");
    removeVertexAG(directGraph, 1);
    displayArrayGraph(directGraph);
    printf("=======================remove edge <2,0>=======================\n");
    removeEdgeAG(directGraph, 2, 0);
    displayArrayGraph(directGraph);
    deleteArrayGraph(undirectGraph);
    deleteArrayGraph(directGraph);
}