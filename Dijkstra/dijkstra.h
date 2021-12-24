#ifndef _DIJKSTRA_
#define _DIJKSTRA_

#include "linkedgraph.h"
#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
# define MAX_INT 9999

int* dijkstra(LinkedGraph* pGraph, int startVertexID);
int getClosestVertexID(int* retList, int* selectVertexID, int maxVertexCount);
int getEdgeWeight(LinkedGraph* pGraph, int fromVertexID, int toVertexID);

#endif