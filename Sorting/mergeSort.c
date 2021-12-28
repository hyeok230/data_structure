#include <stdio.h>
#include <stdlib.h>

void mergeSortInternal(int list[], int* buffer, int start, int middle, int end);

void mergeSort(int list[], int* buffer, int start, int end) {
    int middle;

    middle = 0;
    if (start < end) {
        middle = (start + end) / 2;
        mergeSort(list, buffer, start, middle);
        mergeSort(list, buffer, middle + 1, end);
        mergeSortInternal(list, buffer, start, middle, end);
    }
}

void mergeSortInternal(int list[], int* buffer, int start, int middle, int end) {
    int i, j, k;

    i = start;
    j = middle + 1;
    k = start;
    while (i <= middle && j <= end) {
        if (list[i] <= list[j]) {
            buffer[k] = list[i];
            i++;
        } else {
            buffer[k] = list[j];
            j++;
        }
        k++;
    }
    if (i > middle) {
        for (int t = j; t <= end; t++, k++) {
            buffer[k] = list[t]; 
        }
    } else {
        for (int t = i; t <= middle; t++, k++) {
            buffer[k] = list[t];
        }
    }
    for (int t = start; t <= end; t++) {
        list[t] = buffer[t];
    }
}

void printList(int list[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

int main() {
    int list[] = {5, 8, 7, 1, 6, 2, 4, 3, 9, 10};
    int* buffer;

    buffer = (int*)malloc(sizeof(int) * 10);
    printf("==============Before Sort==============\n");
    printList(list, 10);
    printf("===============After Sort===============\n");
    if (buffer != NULL) {
        mergeSort(list, buffer, 0, 9);
        free(buffer);
    }
    printList(list, 10);
}