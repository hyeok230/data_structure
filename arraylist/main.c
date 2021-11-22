#include "arraylist.h"
#include "stdio.h"
#include "stdlib.h"

ArrayList*	createArrayList(int maxElementCount){
	ArrayList*	pList;
	
	if (maxElementCount > 0)
	{
		pList = (ArrayList*)malloc(sizeof(ArrayList));
		pList->maxElementCount = maxElementCount;
		pList->currentElementCount = 0;
		pList->pElement = (ArrayListNode*)malloc(sizeof(ArrayListNode) * maxElementCount);
	}
	else
	{
		printf("최대 원소 개수는 1개 이상이여야 합니다.");
		pList = NULL;
	}
	return (pList);
}

void deleteArrayList(ArrayList* pList) {
	if (pList == NULL)
	{
		printf("pList error\n");
		return ;
	}
	free(pList->pElement);
	free(pList);
}

int isArrayListFull(ArrayList* pList) {
	if (pList == NULL)
	{
		printf("pList error\n");
		return (FALSE);
	}
	if (pList->currentElementCount == pList->maxElementCount)
		return (TRUE);
	return (FALSE);
}

int addALElement(ArrayList* pList, int position, ArrayListNode element) {
	// currentElementCount 뒤에 넣고자 할땐 반드시 바로 뒤에 넣도록 함
	if (position < 0 || position > pList->currentElementCount)
	{
		printf("position error\n");
		return (FALSE);
	}
	if (pList == NULL)
	{
		printf("pList error\n");
		return (FALSE);
	}
	if (isArrayListFull(pList))
	{
		printf("배열 용량 초과\n");
		return (FALSE);
	}
	for(int i = pList->currentElementCount - 1; i >= position; i--)
		pList->pElement[i + 1] = pList->pElement[i];
	pList->pElement[position] = element;
	pList->currentElementCount++;
	return (TRUE);
}

int removeALElement(ArrayList* pList, int position) {
	if (position < 0 || position >= pList->currentElementCount)
	{
		printf("position error\n");
		return (FALSE);
	}
	if (pList == NULL)
	{
		printf("pList error\n");
		return (FALSE);
	}
	for(int i = position; i < pList->currentElementCount; i++)
		pList->pElement[i] = pList->pElement[i + 1];
	pList->currentElementCount--;
	return (TRUE);
}

ArrayListNode* getALElement(ArrayList* pList, int position) {
	if (position < 0 || position > pList->currentElementCount)
	{
		printf("position error\n");
		return (FALSE);
	}
	if (pList == NULL)
	{
		printf("pList error\n");
		return (NULL);
	}
	return (&pList->pElement[position]);
}

void displayArrayList(ArrayList* pList) {
	if (pList == NULL)
	{
		printf("pList error\n");
		return ;
	}
	for (int i = 0; i < pList->currentElementCount; i++)
		printf("[%d] => %d\n", i, pList->pElement[i].data);
}

void clearArrayList(ArrayList* pList) {
	if (pList == NULL)
	{
		printf("pList error\n");
		return ;
	}
	free(pList->pElement);
	pList->pElement = (ArrayListNode*)malloc(sizeof(ArrayListNode) * pList->maxElementCount);
	pList->currentElementCount = 0;
}

int getArrayListLength(ArrayList* pList) {
	if (pList == NULL)
	{
		printf("pList error\n");
		return (FALSE);
	}
	return (pList->currentElementCount);
}

int main() {
	ArrayList* pList;
	ArrayListNode a;
	a.data = 1;
	ArrayListNode b;
	b.data = 2;
	ArrayListNode c;
	c.data = 3;
	ArrayListNode d;
	d.data = 4;

	pList = createArrayList(10);
	addALElement(pList, 0, a);
	addALElement(pList, 1, c);
	addALElement(pList, 2, d);
	addALElement(pList, 1, b);
	displayArrayList(pList);
	printf("List length : %d\n", getArrayListLength(pList));
	printf("============================================================\n");
	removeALElement(pList, 1);
	printf("remove posiotion 1\n");
	displayArrayList(pList);
	printf("List length : %d\n", getArrayListLength(pList));
	printf("============================================================\n");
	removeALElement(pList, 0);
	printf("remove posiotion 0\n");
	displayArrayList(pList);
	printf("List length : %d\n", getArrayListLength(pList));
	printf("============================================================\n");
	printf("clearArrayList\n");
	clearArrayList(pList);
	displayArrayList(pList);
	printf("List length : %d\n", getArrayListLength(pList));
}
