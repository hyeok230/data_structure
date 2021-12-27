#include <stdio.h>
#include <stdlib.h>

void selectionSort(int list[], int size) {
    int min;
    int temp;
    
    for (int i = 0; i < size - 1; i++) {
        min = i;
        for (int j = i + 1; j < size; j++) {
            if (list[j] < list[min])
                min = j;
        }
        temp = list[i];
        list[i] = list[min];
        list[min] = temp;
    }
}

void printList(int list[], int size) {
    for (int i = 0; i < size - 1; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

int main() {
    int list[] = {5, 8, 7, 1, 6, 2, 4, 3, 9, 10};

    printf("==============Before Sort==============\n");
    printList(list, 10);
    printf("===============After Sort===============\n");
    selectionSort(list, 10);
    printList(list, 10);
}