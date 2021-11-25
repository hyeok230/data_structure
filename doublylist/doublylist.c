#include "doublylist.h"
#include <stdio.h>
#include <stdlib.h>

DoublyList* createDoublyList() {
	DoublyList*	pList;

	pList = (DoublyList*)malloc(sizeof(DoublyList));
	if (pList == NULL)
	{
		printf("malloc error!\n");
		return (NULL);
	}
	pList->currentElementCount = 0;
	pList->headerNode.data = -1;
	pList->headerNode.pLLink = &(pList->headerNode);
	pList->headerNode.pRLink = &(pList->headerNode);
	return (pList);	
}

void deleteDoublyList(DoublyList* pList) {
	if (pList == NULL)
	{
		printf("pList error\n");
		return ;
	}
	clearDoublyList(pList);
	free(pList);
}

int addDLElement(DoublyList* pList, int position, DoublyListNode element) {
	DoublyListNode* preNode;
	DoublyListNode* newNode;

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
	newNode = (DoublyListNode*)malloc(sizeof(DoublyListNode));
	if (newNode == NULL)
	{
		printf("malloc error!\n");
		return (FALSE);
	}
	*newNode = element;
	newNode->pLLink = NULL;
	newNode->pRLink = NULL;
	preNode = &(pList->headerNode);
	for (int i = 0; i < position; i++)
		preNode = preNode->pRLink;
	newNode->pLLink = preNode;
	newNode->pRLink = preNode->pRLink;
	preNode->pRLink = newNode;
	newNode->pRLink->pLLink = newNode;
	pList->currentElementCount++;
	return (TRUE);
}

int removeDLElement(DoublyList* pList, int position) {
	DoublyListNode* delNode;
	
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
	delNode = &(pList->headerNode);
	for (int i = 0; i <= position; i++)
		delNode = delNode->pRLink;
	delNode->pRLink->pLLink = delNode->pLLink;
	delNode->pLLink->pRLink = delNode->pRLink;
	free(delNode);
	pList->currentElementCount--;
	return (TRUE);
}

void clearDoublyList(DoublyList* pList) {
	if (pList == NULL)
	{
		printf("pList error\n");
		return ;
	}
	while (pList->currentElementCount > 0)
		removeDLElement(pList, 0);
}

int getDoublyListLength(DoublyList* pList) {
	if (pList == NULL)
	{
		printf("pList error\n");
		return (FALSE);
	}
	return (pList->currentElementCount);
}

DoublyListNode* getDLElement(DoublyList* pList, int position) {
	DoublyListNode*	retNode;
	
	if (pList == NULL)
	{
		printf("pList error\n");
		return (NULL);
	}
	if (position < 0 || position > pList->currentElementCount)
	{
		printf("position error\n");
		return (NULL);
	}
	retNode = &(pList->headerNode);
	for (int i = 0; i <= position ; i++)
		retNode = retNode->pRLink;
	return (retNode);
}

void displayDoublyList(DoublyList* pList) {
	if (pList == NULL)
	{
		printf("pList error\n");
		return ;
	}
	for (int i = 0; i < pList->currentElementCount; i++)
		printf("index [%d] data -> %d\n", i, getDLElement(pList, i)->data);
}

int	main(){
	DoublyList* pList;
	DoublyListNode pNode;


	pList = createDoublyList();

	pNode.data = 4;
	pNode.pLLink = NULL;
	pNode.pRLink = NULL;
	addDLElement(pList, 0, pNode);
	displayDoublyList(pList);
	printf("=====================================================\n");
	pNode.data = 3;
	pNode.pLLink = NULL;
	pNode.pRLink = NULL;
	addDLElement(pList, 0, pNode);
	displayDoublyList(pList);
	printf("=====================================================\n");
	pNode.data = 2;
	pNode.pLLink = NULL;
	pNode.pRLink = NULL;
	addDLElement(pList, 0, pNode);
	displayDoublyList(pList);
	printf("=====================================================\n");
	pNode.data = 1;
	pNode.pLLink = NULL;
	pNode.pRLink = NULL;
	addDLElement(pList, 0, pNode);
	displayDoublyList(pList);
	printf("=====================================================\n");
	clearDoublyList(pList);
	displayDoublyList(pList);
}
