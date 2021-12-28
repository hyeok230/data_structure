#include "linkeddeque.h"
#include <stdio.h>
#include <stdlib.h>

void radixSort(int list[], int size, int radix, int digit) {
    LinkedDeque** ppDeque;
    DequeNode pNode;
    DequeNode* node;
    int factor;
    int index;

    factor = 1;
    pNode.pLLink = NULL;
    pNode.pRLink = NULL;
    ppDeque = (LinkedDeque**)malloc(sizeof(LinkedDeque*) * radix);
    if (ppDeque == NULL) {
        printf("ppDeque malloc ERROR\n");
        return ;
    }
    for (int i = 0; i < radix; i++) {
        ppDeque[i] = createLinkedDeque();
        if (ppDeque[i] == NULL) {
            for (int j = 0; j < i - 1; j++) {
                if (ppDeque[j] != NULL) {
                    deleteLinkedDeque(ppDeque[j]);
                }
            }
            free(ppDeque);
        }
    }
    for (int i = 0; i < digit; i++) {
        for (index = 0; index < size; index++) {
            pNode.data = list[index];
            insertRearLD(ppDeque[(list[index]/factor)%radix], pNode);
        }
        index = 0;
        for (int j = 0; j < radix; j++) {
            while (isLinkedDequeEmpty(ppDeque[j]) == FALSE) {
                node = deleteFrontLD(ppDeque[j]);
                if (node != NULL) {
                    list[index] = node->data;
                    index++;
                    free(node);
                }
            }
        }
        factor = factor * radix;
    }
    for (int i = 0; i < radix; i++) {
        deleteLinkedDeque(ppDeque[i]);
    }
    free(ppDeque);
}

void printList(int list[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

int main() {
    int list[] = {42, 60, 75, 81, 10, 23, 12, 18};

    printf("==============Before Sort==============\n");
    printList(list, 8);
    printf("===============After Sort===============\n");
    radixSort(list, 8, 10, 2);
    printList(list, 8);
}