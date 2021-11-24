#include "polylist.h"
#include <stdio.h>
#include <stdlib.h>

LinkedList* createLinkedList() {
	LinkedList* pList;

	pList = (LinkedList*)malloc(sizeof(LinkedList));
	if (pList == NULL)
	{
		printf("malloc error!\n");
		return (NULL);
	}
	pList->currentElementCount = 0;
	pList->headerNode.coef = -1;
	pList->headerNode.degree = -1;
	pList->headerNode.pLink = NULL;
	return (pList);
}

int	addPolyNodeLast(LinkedList* pList, float coef, int degree) {
	ListNode* newNode;
	ListNode* pNode;

	if (pList == NULL)
	{
		printf("pList error\n");
		return (FALSE);
	}
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->coef = coef;
	newNode->degree = degree;
	newNode->pLink = NULL;
	pNode = &(pList->headerNode);
	for (int i = 0; i < pList->currentElementCount; i++)
		pNode = pNode->pLink;
	pNode->pLink = newNode;
	pList->currentElementCount++;
	return (TRUE);
}

int	addPoly(LinkedList* aList, LinkedList* bList, LinkedList* cList) {
	ListNode*	aNode;
	ListNode*	bNode;
	int			sum;

	sum = 0;
	if (aList == NULL || bList == NULL || cList == NULL)
	{
		printf("List error\n");
		return (FALSE);
	}
	aNode = aList->headerNode.pLink;
	bNode = bList->headerNode.pLink;
	while (aNode && bNode)
	{
		if (aNode->degree == bNode->degree)
		{
			sum = aNode->coef + bNode->coef;
			addPolyNodeLast(cList, sum, aNode->degree);
			aNode = aNode->pLink;
			bNode = bNode->pLink;
		}
		else if (aNode->degree > bNode->degree)
		{
			addPolyNodeLast(cList, aNode->coef, aNode->degree);
			aNode = aNode->pLink;
		}
		else
		{
			addPolyNodeLast(cList, bNode->coef, bNode->degree);
			bNode = bNode->pLink;
		}
	}
	while (aNode)
	{
		addPolyNodeLast(cList, aNode->coef, aNode->degree);
		aNode = aNode->pLink;
	}
	while (bNode)
	{
		addPolyNodeLast(cList, bNode->coef, bNode->degree);
		bNode = bNode->pLink;
	}
	return (TRUE);
}

ListNode* getLLElement(LinkedList* pList, int position) {
	ListNode* retNode;

	if (pList == NULL)
	{
		printf("pList error\n");
		return (FALSE);
	}
	if (position < 0 || position > pList->currentElementCount)
	{
		printf("position error\n");
		return (FALSE);
	}
	retNode = &(pList->headerNode);
	for (int i = 0; i <= position; i++)
		retNode = retNode->pLink;
	return (retNode);
}

void displayLinkedList(LinkedList* pList)
{
	if (pList == NULL)
	{
		printf("pList error\n");
		return ;
	}
	for (int i = 0; i < pList->currentElementCount; i++)
		printf("index [%d] coef -> %f, degree -> %d\n", i, getLLElement(pList, i)->coef, getLLElement(pList, i)->degree);
}

int main() {
	LinkedList* aList;
	LinkedList* bList;
	LinkedList* cList;

	aList = (LinkedList*)malloc(sizeof(LinkedList));
	bList = (LinkedList*)malloc(sizeof(LinkedList));
	cList = (LinkedList*)malloc(sizeof(LinkedList));
	addPolyNodeLast(aList, 6, 6);
	addPolyNodeLast(aList, 4, 5);
	addPolyNodeLast(aList, 2, 2);
	printf("===============================================\n");
	printf("aList = 6x^6 + 4x^5 + 2x^2\n");
	displayLinkedList(aList);
	printf("===============================================\n");
	addPolyNodeLast(bList, 1, 5);
	addPolyNodeLast(bList, 2, 4);
	addPolyNodeLast(bList, 3, 2);
	addPolyNodeLast(bList, 4, 0);
	printf("bList = 1x^5 + 2x^4 + 3x^2 + 4\n");
	displayLinkedList(bList);
	printf("===============================================\n");
	printf("====================addPoly====================\n");
	printf("cList = 6x^6 + 5x^5 + 2x^4 + 5x^2 + 4\n");
	addPoly(aList, bList, cList);
	displayLinkedList(cList);
}
