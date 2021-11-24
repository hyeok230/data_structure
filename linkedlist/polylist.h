#ifndef _POLYLIST_
#define _POLYLIST_

typedef struct ListNodeType
{
	float coef;
	int degree;
	struct ListNodeType* pLink;
} ListNode;

typedef struct LinkedListType
{
	int currentElementCount;
	ListNode headerNode;
} LinkedList;

LinkedList* createLinkedList();
int addPolyNodeLast(LinkedList* pList, float coef, int degree);
int	addPoly(LinkedList* aList, LinkedList* bList, LinkedList* cList);
ListNode* getLLElement(LinkedList* pList, int position);
void displayLinkedList(LinkedList* pList);
#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif
