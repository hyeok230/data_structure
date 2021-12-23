#ifndef _PRIM_
#define _PRIM_

#include "linkedgraph.h"
#include <stdio.h>
#include <stdlib.h>
# define MAX_INT 9999

typedef struct GraphEdgeType {
    int fromVertexID;
    int toVertexID;
    int weight;
} GraphEdge;

LinkedGraph* mstPrim(LinkedGraph* pGraph, int startVertexID);
void getMinWeightEdge(LinkedGraph* pGraph, LinkedGraph* mstGraph, int fromVertexID, GraphEdge* minWeightEdge, int* vertexUnion);
int checkCycle(int* vertexUnion, int fromVertexID, int toVertexID);
void unionParent(int* vertexUnion, int fromVertexID, int toVertexID);
int getParent(int* vertexUnion, int vertexID);

#endif