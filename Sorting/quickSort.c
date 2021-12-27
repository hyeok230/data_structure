#include <stdio.h>

int partitionQuickSort(int list[], int start, int end);

void quickSort(int list[], int start, int end) {
    int pivot;

    pivot = 0;
    if (start < end) {
        pivot = partitionQuickSort(list, start, end);
        quickSort(list, start, pivot - 1);
        quickSort(list, pivot + 1, end);
    }
}

int partitionQuickSort(int list[], int start, int end) {
    int pivot;
    int left;
    int right;
    int temp;

    left = start;
    right = end;
    pivot = end;
    while (left < right) {
        while ((list[left] < list[pivot]) && (left < right)) {
            left++;
        }
        while ((list[right] > list[pivot]) && (left < right)) {
            right--;
        }
        if (left < right) {
            temp = list[left];
            list[left] = list[right];
            list[right] = temp;
        }
    }
    temp = list[pivot];
    list[pivot] = list[right];
    list[right] = temp;
    return (pivot);
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
    quickSort(list, 0, 9);
    printList(list, 10);
}