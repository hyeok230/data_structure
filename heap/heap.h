#ifndef _HEAP_
#define _HEAP_

typedef struct HeapNodeType
{
	int data;
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
int insertHeap(Heap* pHeap, int data);
HeapNode* deleteHeapNode(Heap* pHeap);

#endif

#ifndef _COMMON_TREE_DEF_
#define _COMMON_TREE_DEF_

#define TRUE		1
#define FALSE		0

#endif