#include <stdio.h>
#include <stdlib.h>
#include "linkeddeque.h"
#include "simdef.h"
#include "simutil.h"

void insertCustomer(int arrivalTime, int processTime, char id, LinkedDeque *pArrivalDeque) {
    DequeNode pNode;

    if (pArrivalDeque == NULL) {
        printf("ERROR\n");
        return ;
    }
    pNode.customer.status = arrival;
    pNode.customer.arrivalTime = arrivalTime;
    pNode.customer.serviceTime = processTime;
    pNode.customer.id = id;
    pNode.customer.startTime = 0;
    pNode.customer.endTime = 0;
    pNode.pLLink = NULL;
    pNode.pRLink = NULL;
    insertRearLD(pArrivalDeque, pNode);
}

void processArrival(int currentTime, LinkedDeque* pArrivalDeque, LinkedDeque* pWaitDeque) {
    DequeNode* pNode;
    int isEmpty;

    if (pArrivalDeque == NULL || pWaitDeque == NULL) {
        printf("ERROR\n");
        return ;        
    }
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
    
    if (pWaitDeque == NULL) {
        printf("ERROR\n");
        return (NULL);       
    }
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
    printf("?????? ?????? => [%d] ", currentTime);
    if (customer.status == arrival) {
        printf("'%c' ?????? ??????\n", customer.id);
    } else if (customer.status == start) {
        printf("'%c' ?????? ????????? ??????, ????????? ?????? => [%d], ?????? ?????? => [%d]\n", customer.id, customer.serviceTime, currentTime - customer.arrivalTime);
    } else {
        printf("%c ?????? ????????? ??????\n", customer.id);
    }
}

void printWaitQueueStatus(int currentTime, LinkedDeque* pWaitDeque) {
    DequeNode* printNode;

    if (pWaitDeque == NULL) {
        printf("ERROR\n");
        return ;       
    }
    printf("?????? ?????? => [%d] ?????? ?????? ??? => [%d] ", currentTime, pWaitDeque->currentElementCount);
    if (pWaitDeque->currentElementCount >0){
        printNode = pWaitDeque->pFrontNode;
        printf("???????????? ?????????");
        for (int i =0; i < pWaitDeque->currentElementCount; i++) {
            printf("[%c]", printNode->customer.id);
            printNode = printNode->pRLink;
        }
    } 
    printf("\n");
}

void printReport(LinkedDeque* pWaitDeque, int serviceUserCount, int totalWaitTime) {
    printf("===================================report===================================\n");
    printf("??????????????? ?????? ?????? ??? => [%d], ???????????? ?????? ??? => [%d], ??? ?????? ?????? => [%d], ?????? ?????? ?????? => [%.2f]\n", pWaitDeque->currentElementCount, serviceUserCount, totalWaitTime, (float)totalWaitTime / serviceUserCount);
}

int main () {
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
    insertCustomer(0, 3, 'a', pArrivalDeque);
    insertCustomer(2, 2, 'b', pArrivalDeque);
    insertCustomer(4, 3, 'c', pArrivalDeque);
    insertCustomer(5, 2, 'd', pArrivalDeque);
    insertCustomer(6, 1, 'e', pArrivalDeque);
    insertCustomer(8, 3, 'f', pArrivalDeque);
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
}