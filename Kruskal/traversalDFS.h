#ifndef _TRAVERSAL_DFS_
#define _TRAVERSAL_DFS_

#include "linkedgraph.h"
#include "linkedstack.h"

int traversalDFS(LinkedGraph* pGraph, int startVertexID, int toVertexID);
int pushLSForDFS(LinkedStack* pStack, int nodeID);

#endif