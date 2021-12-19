#ifndef _TRAVERSAL_BFS_
#define _TRAVERSAL_BFS_

#include "linkeddeque.h"
#include "linkedgraph.h"

int enqueueLQForBFS(LinkedDeque* pQueue, int nodeID);
void traversalBFS(LinkedGraph* pGraph, int startVertexID);

#endif 