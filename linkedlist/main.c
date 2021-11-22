#include "linkedlist.h"
#include "stdio.h"
#include "stdlib.h"

LinkedList* createLinkedList() {
	LinkedList* pList;

	pList = (LinkedList*)malloc(sizeof(LinkedList));
	pList->currentElementCount = 0;
	pList->headerNode.data = -1;
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

int main()
{
	LinkedList* pList;
	ListNode element;
	ListNode element2;
	element.data = 3;
	element.pLink = NULL;
	ListNode* print;

	pList = createLinkedList();
	addLLElement(pList, 0, element);

	element.data = 5;
	element.pLink = NULL;
	addLLElement(pList, 0, element);
	
	print = &(pList->headerNode);
	while(print)
	{
		printf("%d \n", print->data);
		print = print->pLink;
	}
	removeLLElement(pList, 0);
	print = &(pList->headerNode);
	while(print)
	{
		printf("%d \n", print->data);
		print = print->pLink;
	}
	removeLLElement(pList, 0);
	print = &(pList->headerNode);
	while(print)
	{
		printf("%d \n", print->data);
		print = print->pLink;
	}
	printf("=================================================\n");
	clearLinkedList(pList);
	print = &(pList->headerNode);
	while(print)
	{
		printf("%d \n", print->data);
		print = print->pLink;
	}
}
