#ifndef _HEAP_
#define _HEAP_

typedef struct HeapNodeType
{
	int fromVertexID;
	int toVertexID;
	int weight;
} HeapNode;

typedef struct HeapType
{
	int maxElementCount;		
	int currentElementCount;
    HeapNode* pElement;
} Heap;

Heap* createHeap(int maxElementCount);
void deleteHeap(Heap* pHeap);
int isHeapFull(Heap* pHeap);
int isHeapEmpty(Heap* pHeap);
int insertMinHeap(Heap* pHeap, HeapNode element);
HeapNode* deleteMinHeapNode(Heap* pHeap);
void displayHeap(Heap* pHeap);

#endif

#ifndef _COMMON_TREE_DEF_
#define _COMMON_TREE_DEF_

#define TRUE		1
#define FALSE		0

#endif