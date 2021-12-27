#include <stdio.h>

void bubbleSort(int list[], int size) {
    int temp;

    for (int i = size - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++){
            if (list[j] > list[j + 1]) {
                temp = list[j];
                list[j] = list[j + 1];
                list[j+ 1] = temp;     
            }            
        }
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
    bubbleSort(list, 10);
    printList(list, 10);
}