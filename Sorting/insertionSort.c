#include <stdio.h>

void insertionSort(int list[], int size) {
    int temp;
    int i, j;

    for (i = 1; i < size; i++) {
        temp = list[i];
        j = i;
        while ((j > 0) && list[j - 1] > temp) {
            list[j] = list[j - 1];
            j = j - 1;
        }
        list[j] = temp;
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

    printf("==============Before Sort==============\n");
    printList(list, 10);
    printf("===============After Sort===============\n");
    insertionSort(list, 10);
    printList(list, 10);
}