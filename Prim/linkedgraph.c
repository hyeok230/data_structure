#include "linkedgraph.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

LinkedGraph* createLinkedGraph(int maxVertexCount) {
    LinkedGraph* pGraph;

    if (maxVertexCount <= 0) {
        printf("maxVertexCount ERROR\n");
        return (NULL);
    }
    pGraph = (LinkedGraph*)malloc(sizeof(LinkedGraph));
    if (pGraph == NULL) {
        printf("pGraph malloc ERROR\n");
        return (NULL);
    }
    pGraph->maxVertexCount = maxVertexCount;
    pGraph->currentVertexCount = 0;
    pGraph->currentEdgeCount = 0;
    pGraph->graphType = GRAPH_UNDIRECTED;
    pGraph->pVertex = (int*)malloc(sizeof(int) * maxVertexCount);
    if (pGraph->pVertex == NULL) {
        printf("pVertex malloc ERROR\n");
        return (NULL);
    }
    memset(pGraph->pVertex, NOT_USED, sizeof(int) * maxVertexCount);
    pGraph->ppAdjEdge = (LinkedList**)malloc(sizeof(LinkedList*) * maxVertexCount);
    if (pGraph->ppAdjEdge == NULL) {
        printf("ppAdjEdge malloc ERROR\n");
        return (NULL);
    }
    for (int i = 0; i < maxVertexCount; i++) {
        pGraph->ppAdjEdge[i] = createLinkedList();
        if (pGraph->ppAdjEdge[i] == NULL) {
            printf("ppAdjEdge[%d] malloc ERROR\n", i);
            return (NULL);
        }
        pGraph->ppAdjEdge[i]->headerNode.vertexID = i;
    }
    return (pGraph);
}

LinkedGraph* createLinkedDirectedGraph(int maxVertexCount) {
    LinkedGraph* pGraph;

    pGraph = createLinkedGraph(maxVertexCount);
    pGraph->graphType = GRAPH_DIRECTED;
    return (pGraph);
}

void deleteLinkedGraph(LinkedGraph* pGraph) {
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return ;
    }
    for (int i = 0; i < pGraph->maxVertexCount; i++) {
        deleteLinkedList(pGraph->ppAdjEdge[i]);
    }
    free(pGraph->ppAdjEdge);
    free(pGraph->pVertex);
    free(pGraph);
}

int isEmptyLG(LinkedGraph* pGraph) {
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (FALSE);
    }
    if (pGraph->currentVertexCount == 0) {
        return (TRUE);
    }
    return (FALSE);
}

int addVertexLG(LinkedGraph* pGraph, int vertexID) {
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (FAIL);
    }
    if (pGraph->pVertex[vertexID] == NOT_USED) {
        pGraph->pVertex[vertexID] = USED;
        pGraph->currentVertexCount++;
        return (TRUE);
    }
    return (FAIL);
}

int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID) {
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (FAIL);
    }
    addEdgewithWeightLG(pGraph, fromVertexID, toVertexID, 1);
}

int addEdgewithWeightLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight) {
    ListNode newElement;
    
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (FAIL);
    }
    if (checkVertexValid(pGraph, fromVertexID) == FALSE || checkVertexValid(pGraph, toVertexID) == FALSE) {
        printf("VertexID invalid ERROR\n");
        return (FAIL);
    }
    newElement.vertexID = toVertexID;
    newElement.weight = weight;
    newElement.pLink = NULL;
    if (checkEdgeExist(pGraph, fromVertexID, toVertexID) == FALSE) {
        if (addLLElement(pGraph->ppAdjEdge[fromVertexID], 0, newElement) == FALSE) {
            printf("add Element ERROR\n");
            return (FAIL);
        }
        pGraph->currentEdgeCount++; 
        if (pGraph->graphType == GRAPH_UNDIRECTED) {
            addEdgewithWeightLG(pGraph, toVertexID, fromVertexID, weight);
        }
    } else {
        return (FAIL);
    }
}

int checkEdgeExist(LinkedGraph* pGraph, int fromVertexID, int toVertexID) {
    ListNode* pNode;
    
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (FALSE);
    }
    pNode = pGraph->ppAdjEdge[fromVertexID]->headerNode.pLink;
    while (pNode) {
        if (pNode->vertexID == toVertexID) {
            return (TRUE);
        }
        pNode = pNode->pLink;
    }
    return (FALSE);
}

int checkVertexValid(LinkedGraph* pGraph, int vertexID) {
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (FALSE);
    }
    if (pGraph->pVertex[vertexID] == USED) {
        return (TRUE);
    }
    return (FALSE);
}

int removeVertexLG(LinkedGraph* pGraph, int vertexID) {
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (FAIL);
    }
    if (pGraph->pVertex[vertexID] == NOT_USED) {
        printf("vertexID already not used\n");
        return (FAIL);
    } 
    pGraph->pVertex[vertexID] = NOT_USED;
    pGraph->currentVertexCount--;
    pGraph->currentEdgeCount  =  pGraph->currentEdgeCount - pGraph->ppAdjEdge[vertexID]->currentElementCount;
    clearLinkedList(pGraph->ppAdjEdge[vertexID]);
    for (int i = 0; i < pGraph->maxVertexCount; i++) {
        if (i == vertexID) {
            continue ;
        }
        removeEdgeLG(pGraph, i, vertexID);
    }
    return (SUCCESS);
}

int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID) {
    int result;
    
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (FAIL);
    }
    if (checkVertexValid(pGraph, fromVertexID) == FALSE || checkVertexValid(pGraph, fromVertexID) == FALSE) {
        return (FAIL);
    }
    if (checkEdgeExist(pGraph, fromVertexID, toVertexID) == TRUE) {
        for (int i = 0; i < pGraph->ppAdjEdge[fromVertexID]->currentElementCount; i++) {
            if (getLLElement(pGraph->ppAdjEdge[fromVertexID], i)->vertexID == toVertexID) {
                result = removeLLElement(pGraph->ppAdjEdge[fromVertexID], i);
                break;
            }
        }
        pGraph->currentEdgeCount--;
        if (pGraph->graphType == GRAPH_UNDIRECTED) {
            result = removeEdgeLG(pGraph, toVertexID, fromVertexID);
        }
        return (result);
    }
    return (FALSE);
}

// void deleteGraphNode(LinkedList* pList, int delVertexID) {
//     if (pList == NULL) {
//         printf("pList ERROR\n");
//         return ;
//     }
// }

// int findGraphNodePosition(LinkedList* pList, int vertexID) {
//     if (pList == NULL) {
//         printf("pList ERROR\n");
//         return (FAIL);
//     }
// }

int getEdgeCountLG(LinkedGraph* pGraph) {
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (FAIL);
    }
    return (pGraph->currentEdgeCount);
}

int getVertexCountLG(LinkedGraph* pGraph) {
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (FAIL);
    }
    return (pGraph->currentVertexCount);
}

int getMaxVertexCountLG(LinkedGraph* pGraph) {
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (FAIL);
    }
    return (pGraph->maxVertexCount);
}

int getGraphTypeLG(LinkedGraph* pGraph) {
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return (FAIL);
    }
    return (pGraph->graphType);
}

void displayLinkedGraph(LinkedGraph* pGraph) {
    if (pGraph == NULL) {
        printf("pGraph ERROR\n");
        return ;
    }
    for (int i = 0; i < pGraph->maxVertexCount; i++) {
        if (checkVertexValid(pGraph, i) == TRUE) {
            printf("Node [%d] Linked Nodes =>", i);
            displayLinkedList(pGraph->ppAdjEdge[i]);
            printf("\n");
        }
    }
}