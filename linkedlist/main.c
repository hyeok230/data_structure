#include "linkedlist.h"
#include "stdio.h"
#include "stdlib.h"

LinkedList* createLinkedList() {
	LinkedList* pList;

	pList = (LinkedList*)malloc(sizeof(LinkedList));
	pList->currentElementCount = 0;
	pList->headerNode.data = 0;
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
	if (position < 0 || position > pList->currentCount)
	{
		printf("position error\n");
		return (FALSE);
	}
	newNode = &element;
	preNode = &(pList->headerNode);
	for (int i = 0; i < position; i++)
		preNode = preNode->pLink;
	newNode->pLink = preNode->pLink;
	preNode->pLink = newNode;
	pList->currentCount++;
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
	if (position < 0 || position > pList->currentCount)
	{
		printf("position error\n");
		return (FALSE);
	}
	preNode = &(pList->headerNode);
	for (int i = 0; i < position; i++)
		preNode = preNode->pLink;
	delNode = preNode->pLink;
	preNode->pLink = delNode->pLink;
	pList->currentCount--;
}

ListNode* getLLElement(LinkedList* pList, int position) {
	ListNode* retNode;

	if (pList == NULL)
	{
		printf("pList error\n");
		return (FALSE);
	}
	if (position < 0 || position > pList->currentCount)
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
		return (FALSE);
	}
	if (pList->currentCount > 0)
		free(pList->headerNode.pLink);
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
		return (FALSE);
	}
	if (pList->currentCount > 0)
		free(pList->headerNode.pLink);
}

int main()
{
	LinkedList* pList;

	pList = createLinkedList();
}
