#include "linkeddeque.h"
#include <stdio.h>
#include <stdlib.h>

LinkedDeque* createLinkedDeque() {
    LinkedDeque* pDeque;

    pDeque = (LinkedDeque*)malloc(sizeof(LinkedDeque));
    if (pDeque == NULL) {
        printf("malloc ERROR\n");
        return (NULL);
    }
    pDeque->currentElementCount = 0;
    pDeque->pFrontNode = NULL;
    pDeque->pRearNode = NULL;
    return (pDeque);
}

int insertFrontLD(LinkedDeque* pDeque, DequeNode element) {
    DequeNode* newNode;

    if (pDeque == NULL) {
        printf("pDeque Error\n");
        return (FALSE);
    }
    newNode = (DequeNode*)malloc(sizeof(DequeNode));
    if (newNode == NULL) {
        printf("malloc Error\n");
        return (FALSE);
    }
    *newNode = element;
    newNode->pLLink = NULL;
    newNode->pRLink = NULL;
    if (pDeque->currentElementCount == 0) {
        pDeque->pFrontNode = newNode;
        pDeque->pRearNode = newNode;
    } else {
        pDeque->pFrontNode->pLLink = newNode;
        newNode->pRLink = pDeque->pFrontNode;
        pDeque->pFrontNode = newNode;
    }
    pDeque->currentElementCount++;
    return (TRUE);
}

int insertRearLD(LinkedDeque* pDeque, DequeNode element) {
    DequeNode* newNode;

    if (pDeque == NULL) {
        printf("pDeque Error\n");
        return (FALSE);
    }
    newNode = (DequeNode*)malloc(sizeof(DequeNode));
    if (newNode == NULL) {
        printf("malloc Error\n");
        return (FALSE);
    }
    *newNode = element;
    newNode->pLLink = NULL;
    newNode->pRLink = NULL;
    if (pDeque->currentElementCount == 0) {
        pDeque->pFrontNode = newNode;
        pDeque->pRearNode = newNode;
    } else {
        pDeque->pRearNode->pRLink = newNode;
        newNode->pLLink = pDeque->pRearNode;
        pDeque->pRearNode = newNode;
    }
    pDeque->currentElementCount++;
    return (TRUE);
}

DequeNode* deleteFrontLD(LinkedDeque* pDeque) {
    DequeNode* retNode;
    
    if (pDeque == NULL) {
        printf("pDeque Error\n");
        return (NULL);
    }
    if (isLinkedDequeEmpty(pDeque)) {
        printf("pDeque empty Error\n");
        return (NULL);
    }
    retNode = pDeque->pFrontNode;
    pDeque->pFrontNode = pDeque->pFrontNode->pRLink;
    retNode->pRLink = NULL;
    if (pDeque->currentElementCount == 1) {
        pDeque->pRearNode = NULL;
    } else {
        pDeque->pFrontNode->pLLink = NULL;
    }
    pDeque->currentElementCount--;
    return (retNode);
}

DequeNode* deleteRearLD(LinkedDeque* pDeque) {
    DequeNode* retNode;

    if (pDeque == NULL) {
        printf("pDeque Error\n");
        return (NULL);
    }
    if (isLinkedDequeEmpty(pDeque)) {
        printf("pDeque empty Error\n");
        return (NULL);
    }
    retNode = pDeque->pRearNode;
    pDeque->pRearNode = pDeque->pRearNode->pLLink;
    retNode->pLLink = NULL;
    if (pDeque->currentElementCount == 1) {
        pDeque->pFrontNode = NULL;
    } else {
        pDeque->pRearNode->pRLink = NULL;
    }
    pDeque->currentElementCount--;
    return (retNode);
}

DequeNode* peekFrontLD(LinkedDeque* pDeque) {
    if (pDeque == NULL) {
        printf("pDeque Error\n");
        return (NULL);
    }
    if (isLinkedDequeEmpty(pDeque)) {
        printf("pDeque empty Error\n");
        return (NULL);
    }
    return (pDeque->pFrontNode);
}

DequeNode* peekRearLD(LinkedDeque* pDeque) {
    if (pDeque == NULL) {
        printf("pDeque Error\n");
        return (NULL);
    }
    if (isLinkedDequeEmpty(pDeque)) {
        printf("pDeque empty Error\n");
        return (NULL);
    }
    return (pDeque->pRearNode);
}

void deleteLinkedDeque(LinkedDeque* pDeque) {
    DequeNode* delNode;
    
    if (pDeque == NULL) {
        printf("pDeque Error\n");
        return ;
    }
    while (pDeque->currentElementCount != 0) {
        delNode = deleteFrontLD(pDeque);
        free(delNode);
    }
}

int isLinkedDequeFull(LinkedDeque* pDeque) {
    if (pDeque == NULL) {
        printf("pDeque Error\n");
        return (FALSE);
    }
    return (TRUE);
}

int isLinkedDequeEmpty(LinkedDeque* pDeque) {
    if (pDeque == NULL) {
        printf("pDeque Error\n");
        return (FALSE);
    }
    if (pDeque->currentElementCount == 0) {
        return (TRUE);
    }
    return (FALSE);
}

void displayDeque(LinkedDeque* pDeque) {
    DequeNode* printNode;

    if (pDeque == NULL) {
        printf("pDeque Error\n");
        return ;
    }
    printNode = pDeque->pFrontNode;
    for (int i =0; i < pDeque->currentElementCount; i++) {
        printf("data => [%d]\n", printNode->data);
        printNode = printNode->pRLink;
    }
}