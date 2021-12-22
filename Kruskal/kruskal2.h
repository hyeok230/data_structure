#ifndef _KRUSKAL2_
#define _KRUSKAL2_

#include "linkedgraph.h"
#include "heap.h"
#include "linkedstack.h"
#include <stdio.h>
#include <stdlib.h>

LinkedGraph* mstKruskal(LinkedGraph* pGraph);
void unionParent(int* vertexUnion, int fromVertexID, int toVertexID);
int getParent(int* vertexUnion, int vertexID);
int checkCycle(int* vertexUnion, int fromVertexID, int toVertexID);
Heap* orderEdges(LinkedGraph* pGraph);

#endif