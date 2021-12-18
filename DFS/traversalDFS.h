#ifndef _TRAVERSAL_DFS_
#define _TRAVERSAL_DFS_

#include "linkedgraph.h"
#include "linkedstack.h"

void traversalDFS(LinkedGraph* pGraph, int startVertexID);
int pushLSForDFS(LinkedStack* pStack, int nodeID);

#endif