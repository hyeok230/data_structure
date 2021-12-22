#ifndef _KRUSKAL_
#define _KRUSKAL_

#include "heap.h"
#include "linkedgraph.h"
#include "linkedstack.h"
#include "traversalDFS.h"

LinkedGraph* mstKruskal(LinkedGraph* pGraph);
Heap* orderEdges(LinkedGraph* pGraph);
int checkCycle(LinkedGraph* pGraph, int fromVertexID, int toVertexID);

#endif