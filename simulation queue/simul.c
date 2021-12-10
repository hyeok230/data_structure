#include <stdio.h>
#include <stdlib.h>
#include "linkeddeque.h"
#include "simdef.h"
#include "simutil.h"

void insertCustomer(int arrivalTime, int processTime, LinkedDeque *pArrivalDeque) {
    DequeNode pNode;

    pNode.customer.status = arrival;
    pNode.customer.arrivalTime = arrivalTime;
    pNode.customer.serviceTime = processTime;
    pNode.customer.startTime = 0;
    pNode.customer.endTime = 0;
    pNode.pLLink = NULL;
    pNode.pRLink = NULL;
    insertRearLD(pArrivalDeque, pNode);
}

void processArrival(int currentTime, LinkedDeque* pArrivalDeque, LinkedDeque* pWaitDeque) {
    DequeNode* pNode;
    int isEmpty;

    isEmpty = isLinkedDequeEmpty(pArrivalDeque);
    while(isEmpty == FALSE) {
        pNode = peekFrontLD(pArrivalDeque);
        if (currentTime == pNode->customer.arrivalTime) {
            insertRearLD(pWaitDeque, *pNode);
            printSimCustomer(currentTime, pNode->customer);
            free(deleteFrontLD(pArrivalDeque));
        } else {
            break;
        }
        isEmpty = isLinkedDequeEmpty(pArrivalDeque);
    }
    
}

DequeNode* processServiceNodeStart(int currentTime, LinkedDeque* pWaitDeque) {
    DequeNode* pServiceNode;
    
    pServiceNode = NULL;
    if (isLinkedDequeEmpty(pWaitDeque) == FALSE) {
        pServiceNode = deleteFrontLD(pWaitDeque);
        pServiceNode->customer.status = start;
        pServiceNode->customer.startTime = currentTime;
        printSimCustomer(currentTime, pServiceNode->customer);
    }
    return (pServiceNode);
}

DequeNode* processServiceNodeEnd(int currentTime, DequeNode* pServiceNode, int* pServiceUserCount, int *pTotalWaitTime) {
    int endTime;

    endTime = pServiceNode->customer.startTime + pServiceNode->customer.serviceTime;
    if (endTime == currentTime) {
        (*pTotalWaitTime) += pServiceNode->customer.startTime - pServiceNode->customer.arrivalTime;
        (*pServiceUserCount)++;
        pServiceNode->customer.status = end;
        pServiceNode->customer.endTime = currentTime;
        printSimCustomer(currentTime, pServiceNode->customer);
        free(pServiceNode);
        return (NULL);
    } else {
        return (pServiceNode);
    }
}

void printSimCustomer(int currentTime, SimCustomer customer) {
    printf("현재 시각 => [%d] ", currentTime);
    if (customer.status == arrival) {
        printf("고객 도착\n");
    } else if (customer.status == start) {
        printf("고객 서비스 시작, 도착 시간 => [%d] 대기 시간 => [%d]\n", customer.arrivalTime, currentTime - customer.arrivalTime);
    } else {
        printf("고객 서비스 종료\n");
    }
}

void printWaitQueueStatus(int currentTime, LinkedDeque* pWaitDeque) {
    printf("현재 시각 => [%d] 대기 고객 수 => [%d]\n", currentTime, pWaitDeque->currentElementCount);
}

void printReport(LinkedDeque* pWaitDeque, int serviceUserCount, int totalWaitTime) {
    printf("==========================report==========================\n");
    printf("서비스하지 못한 고객 수 => [%d], 서비스한 고객 수 => [%d], 총 대기 시간 => [%d], 평균 대기 시간 => [%.2f]\n", pWaitDeque->currentElementCount, serviceUserCount, totalWaitTime, (float)totalWaitTime / serviceUserCount);
}

void main () {
    int serviceUserCount;
    int totalWaitTime;
    int endTime;
    LinkedDeque* pArrivalDeque;
    LinkedDeque* pWaitDeque;
    DequeNode* pServiceNode;

    serviceUserCount = 0;
    totalWaitTime = 0;
    endTime = 10;
    pArrivalDeque = createLinkedDeque();
    pWaitDeque = createLinkedDeque();
    pServiceNode = NULL;
    insertCustomer(0, 3, pArrivalDeque);
    insertCustomer(2, 2, pArrivalDeque);
    insertCustomer(4, 3, pArrivalDeque);
    insertCustomer(5, 2, pArrivalDeque);
    insertCustomer(6, 1, pArrivalDeque);
    insertCustomer(8, 3, pArrivalDeque);
    for (int currentTime = 0; currentTime < endTime; currentTime++) {
        processArrival(currentTime, pArrivalDeque, pWaitDeque);

        if (pServiceNode != NULL) {
            pServiceNode = processServiceNodeEnd(currentTime, pServiceNode, &serviceUserCount, &totalWaitTime);
        }
        if (pServiceNode == NULL) {
            pServiceNode = processServiceNodeStart(currentTime, pWaitDeque);
        }
        printWaitQueueStatus(currentTime, pWaitDeque);
    }
    printReport(pWaitDeque, serviceUserCount, totalWaitTime);
    if (pServiceNode != NULL) {
        free(pServiceNode);
    }
    free(pArrivalDeque);
    free(pWaitDeque);
    while(1);
}