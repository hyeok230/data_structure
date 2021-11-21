#include "arraylist.h"
#include "stdio.h"
#include "stdlib.h"

ArrayList*	createArrayList(int maxElementCount){
	ArrayList*	pList;

	pList = (ArrayList*)malloc(sizeof(ArrayList));
	pList->maxElementCount = maxElementCount;
	pList->currentElementCount = 0;
	pList->pElement = (ArrayListNode*)malloc(sizeof(ArrayListNode) * maxElementCount);
	return (pList);
}

void deleteArrayList(ArrayList* pList) {
	free(pList->pElement);
	free(pList);
}

int isArrayListFull(ArrayList* pList) {
	if (pList->currentElementCount == pList->maxElementCount)
		return (TRUE);
	return (FALSE);
}

int addALElement(ArrayList* pList, int position, ArrayListNode element) {
	// currentElementCount 뒤에 넣고자 할땐 반드시 바로 뒤에 넣도록 함
	if (position >= pList->maxElementCount)
		return (FALSE);
	if (isArrayListFull(pList))
		return (FALSE);
	if (pList->currentElementCount == 0)
		pList->pElement[0] = element;
	else
		for (int i = pList->currentElementCount; i > position; i--)
			pList->pElement[i] = pList->pElement[i - 1];
		pList->pElement[position] = element;
	pList->currentElementCount++;
	return (TRUE);
}

int removeALElement(ArrayList* pList, int position) {
	
	return (FALSE);
}

ArrayListNode* getALElement(ArrayList* pList, int position) {
	if (position >= pList->currentElementCount)
		return (NULL);
	else
		return (&pList->pElement[position]);
}

void displayArrayList(ArrayList* pList) {
	for (int i = 0; i < pList->currentElementCount; i++)
		printf("[%d] => %d\n", i, pList->pElement[i].data);
}

void clearArrayList(ArrayList* pList) {
	free(pList->pElement);
	pList->pElement = (ArrayListNode*)malloc(sizeof(ArrayListNode) * pList->maxElementCount);
	pList->currentElementCount = 0;
}

int getArrayListLength(ArrayList* pList) {
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
	clearArrayList(pList);
	displayArrayList(pList);
}
