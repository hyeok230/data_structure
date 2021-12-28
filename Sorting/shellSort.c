#include <stdio.h>

void shellInsertionSort(int list[], int start, int end, int interval);

void shellSort(int list[], int size) {
    int interval;

    interval = size / 2;
    while (interval > 0) {
        for (int i = 0; i < interval; i++) {
            shellInsertionSort(list, i, size - 1, interval);
        }
        interval = interval / 2;
    }
}

void shellInsertionSort(int list[], int start, int end, int interval) {
    int index;
    int temp;

    for (int i = start + interval; i <= end; i = i + interval) {
        temp = list[i];
        index = i - interval;
        while ((index >= start) && temp < list[index]) {
            list[index + interval] = list[index];
            index = index - interval;
        }
        list[index + interval] = temp;
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
    shellSort(list, 10);
    printList(list, 10);
}