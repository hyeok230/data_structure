#include "linkedlist.h"
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
	pList->headerNode.vertexID = -1;
	pList->headerNode.weight = 0;
	pList->headerNode.pLink = NULL;
	return (pList);
}

int addLLElement(LinkedList* pList, int position, ListNode element) {
	ListNode* preNode;
	ListNode* newNode;
	
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
	newNode = (ListNode*)malloc(sizeof(ListNode));
	*newNode = element;
	newNode->pLink = NULL;
	preNode = &(pList->headerNode);
	for (int i = 0; i < position; i++)
		preNode = preNode->pLink;
	newNode->pLink = preNode->pLink;
	preNode->pLink = newNode;
	pList->currentElementCount++;
	return (TRUE);
}

int removeLLElement(LinkedList* pList, int position) {
	ListNode* preNode;
	ListNode* delNode;

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
	preNode = &(pList->headerNode);
	for (int i = 0; i < position; i++)
		preNode = preNode->pLink;
	delNode = preNode->pLink;
	preNode->pLink = delNode->pLink;
	free(delNode);
	pList->currentElementCount--;
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

void clearLinkedList(LinkedList* pList) {
	if (pList == NULL)
	{
		printf("pList error\n");
		return ;
	}
	while (pList->currentElementCount > 0)
		removeLLElement(pList, 0);
}

int getLinkedListLength(LinkedList* pList) {
	if (pList == NULL)
	{
		printf("pList error\n");
		return (FALSE);
	}
	return (pList->currentElementCount);
}

void deleteLinkedList(LinkedList* pList) {
	if (pList == NULL)
	{
		printf("pList error\n");
		return ;
	}
	clearLinkedList(pList);
	free(pList);
}

void displayLinkedList(LinkedList* pList)
{
	if (pList == NULL)
	{
		printf("pList error\n");
		return ;
	}
	for (int i = 0; i < pList->currentElementCount; i++)
		printf("| vertexID -> [%d] weight -> [%d] | ", getLLElement(pList, i)->vertexID, getLLElement(pList, i)->weight);
}

void reverseLinkedList(LinkedList* pList)
{
	ListNode* preNode;
	ListNode* currentNode;
	ListNode* pNode;

	if (pList == NULL)
	{
		printf("pList error\n");
		return ;
	}
	preNode = NULL;
	currentNode = NULL;
	pNode = pList->headerNode.pLink;
	while (pNode != NULL)
	{
		preNode = currentNode;
		currentNode = pNode;
		pNode = pNode->pLink;
		currentNode->pLink = preNode;
	}
	pList->headerNode.pLink = currentNode;
}