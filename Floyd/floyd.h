#ifndef _FLOYD_
#define _FLOYD_

#include "linkedlist.h"
#include "linkedgraph.h"
#include <stdio.h>
#include <stdlib.h>
# define MAX_INT 9999

int** floyd(LinkedGraph* pGraph);
int getEdgeWeight(LinkedGraph* pGraph, int fromVertexID, int toVertexID);

#endif 