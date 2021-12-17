#include "binsearchtree.h"
#include <stdio.h>
#include <stdlib.h>

BinSearchTree* createBinSearchTree() {
    BinSearchTree* pBinSearchTree;

    pBinSearchTree = (BinSearchTree*)malloc(sizeof(BinSearchTree));
    if (pBinSearchTree == NULL) {
        printf("pBinSearchTree malloc ERROR\n");
        return (NULL);
    }
    pBinSearchTree->pRootNode = NULL;
    return (pBinSearchTree);
}

int insertElementBST(BinSearchTree* pBinSearchTree, BinSearchTreeNode element) {
    BinSearchTreeNode* parentNode;
    BinSearchTreeNode* newNode;
    
    if (pBinSearchTree == NULL) {
        printf("pBinSearchTree ERROR\n");
        return (FALSE);
    }
    parentNode = pBinSearchTree->pRootNode;
    while (parentNode) {
        if (parentNode->key == element.key) {
            printf("key value ERROR\n");
            return (FALSE);
        } else if (parentNode->key > element.key) {
            if (parentNode->pLeftChild == NULL)
                break;
            parentNode = parentNode->pLeftChild;
        } else {
            if (parentNode->pRightChild == NULL)
                break;
            parentNode = parentNode->pRightChild;
        }
    }
    newNode = (BinSearchTreeNode*)malloc(sizeof(BinSearchTreeNode));
    if (newNode == NULL) {
        printf("newNode malloc ERROR\n");
        return (FALSE);
    }
    *newNode = element;
    if (parentNode == NULL) {
        pBinSearchTree->pRootNode = newNode;
    } else {
        if (parentNode->key > newNode->key) {
            parentNode->pLeftChild = newNode;
        } else {
            parentNode->pRightChild = newNode;
        }
    } 
    return (TRUE);
}

BinSearchTreeNode* insertInternalRecursiveElementBST(BinSearchTreeNode* pNode, BinSearchTreeNode element) {
    if (pNode == NULL) {
        pNode = (BinSearchTreeNode*)malloc(sizeof(BinSearchTreeNode));
        if (pNode == NULL) {
            printf("pNode malloc ERROR\n");
            return (NULL);
        }
        *pNode = element;
    } else {
        if (pNode->key > element.key) {
            pNode->pLeftChild = insertInternalRecursiveElementBST(pNode->pLeftChild, element);
        } else if (pNode->key == element.key) {
            printf("key value ERROR\n");
            return (NULL);
        } else {
            pNode->pRightChild = insertInternalRecursiveElementBST(pNode->pRightChild, element);
        } 
    }
    return (pNode);
}

int insertRecursiveElementBST(BinSearchTree* pBinSearchTree, BinSearchTreeNode element) {
    if (pBinSearchTree == NULL) {
        printf("pBinSearchTree ERROR\n");
        return (FALSE);
    }
    if (pBinSearchTree->pRootNode == NULL) {
        pBinSearchTree->pRootNode = (BinSearchTreeNode*)malloc(sizeof(BinSearchTreeNode));
        if (pBinSearchTree->pRootNode == NULL) {
            printf("pBinSearchTree->pRootNode malloc ERROR\n");
            return (FALSE);
        }
        *(pBinSearchTree->pRootNode) = element;
    } else {
        if (insertInternalRecursiveElementBST(pBinSearchTree->pRootNode, element) == NULL) {
            printf("insert ERROR\n");
            return (FALSE);
        }
    }
    return (TRUE);
}


int deleteElementBST(BinSearchTree* pBinSearchTree, int key) {
    BinSearchTreeNode* parentNode;
    BinSearchTreeNode* delNode;
    BinSearchTreeNode* successorNode;
    BinSearchTreeNode* parentSuccessorNode;
    BinSearchTreeNode* childNode;

    if (pBinSearchTree == NULL) {
        printf("pBinSearchTree ERRO\n");
        return (FALSE);
    }
    parentNode = NULL;
    delNode = pBinSearchTree->pRootNode;
    while (delNode) {
        if (delNode->key == key) {
            break ;
        }
        parentNode = delNode;
        if (delNode->key > key) {
            delNode = delNode->pLeftChild;
        } else {
            delNode = delNode->pRightChild;
        }
    }
    if (delNode == NULL) {
        printf("key value does not exist ERROR\n");
        return (FALSE);
    }
    // delNode의 자식 노드가 없는 경우
    if (delNode->pLeftChild == NULL && delNode->pRightChild == NULL) {
        if (parentNode != NULL) {
            if (parentNode->pLeftChild == delNode) {
                parentNode->pLeftChild = NULL;
            } else {
                parentNode->pRightChild = NULL;
            }
        } else {
            pBinSearchTree->pRootNode = NULL;
        }
    } else if ((delNode->pLeftChild == NULL) || (delNode->pRightChild == NULL)) {
        // delNode의 자식 노드가 하나인 경우
        if (delNode->pLeftChild != NULL) {
            childNode = delNode->pLeftChild;
        } else {
            childNode = delNode->pRightChild;
        }
        if (parentNode != NULL) {
            if (parentNode->pLeftChild == delNode) {
                parentNode->pLeftChild = childNode;
            } else {
                parentNode->pRightChild = childNode;
            }
        } else {
            pBinSearchTree->pRootNode = childNode;
        }
    } else {
        // delNode의 자식 노드가 두개인 경우
        parentSuccessorNode = delNode;
        successorNode = delNode->pLeftChild;
        while (successorNode->pRightChild) {
            parentSuccessorNode = successorNode;
            successorNode = successorNode->pRightChild;
        }
        if (parentSuccessorNode->pLeftChild == successorNode) {
            parentSuccessorNode->pLeftChild = successorNode->pLeftChild;
        } else {
            parentSuccessorNode->pRightChild = successorNode->pLeftChild;
        }
        delNode->key = successorNode->key;
        delNode->value = successorNode->value;
        delNode = successorNode;
    }
    free(delNode);
    return (TRUE);
}

BinSearchTreeNode* findMinNode(BinSearchTreeNode* pNode) {
    BinSearchTreeNode* tmpNode;

    tmpNode = pNode;
    while (tmpNode->pLeftChild) {
        tmpNode = tmpNode->pLeftChild;
    }
    return (tmpNode);
}

BinSearchTreeNode* deleteInternalRecursiveElementBST(BinSearchTreeNode* pNode, int key) {
    BinSearchTreeNode* successorNode;

    successorNode = NULL;
    if (pNode == NULL) {
        return (NULL);
    }
    if (pNode->key > key) {
        pNode->pLeftChild = deleteInternalRecursiveElementBST(pNode->pLeftChild, key);
    } else if (pNode->key < key) {
        pNode->pRightChild = deleteInternalRecursiveElementBST(pNode->pRightChild, key);
    } else {
        if (pNode->pLeftChild != NULL && pNode->pRightChild != NULL) {
            successorNode = findMinNode(pNode->pRightChild);
            pNode->key = successorNode->key;
            pNode->value = successorNode->value;
            pNode->pRightChild = deleteInternalRecursiveElementBST(pNode->pRightChild, successorNode->key);
        } else {
            successorNode = (pNode->pLeftChild == NULL) ? pNode->pRightChild : pNode->pRightChild;
            free(pNode);
            return (successorNode);
        }
    }
}

int deleteRecursiveElementBST(BinSearchTree* pBinSearchTree, int key) {
    if (pBinSearchTree == NULL) {
        printf("pBinSearchTree ERROR\n");
        return (FALSE);
    }
    if (deleteInternalRecursiveElementBST(pBinSearchTree->pRootNode, key) == NULL) {
        printf("delete ERROR\n");
        return FALSE;
    }
    return (TRUE);
}

BinSearchTreeNode* searchRecursiveBST(BinSearchTree* pBinSearchTree, int key) {
    if (pBinSearchTree == NULL) {
        printf("pBinSearchTree ERROR\n");
        return (NULL);
    }
    return (searchInternalRecursiveBST(pBinSearchTree->pRootNode, key));
}

BinSearchTreeNode* searchInternalRecursiveBST(BinSearchTreeNode* pTreeNode, int key) {
    if (pTreeNode->key == key) {
        return (pTreeNode);
    } else if (pTreeNode->key > key) {
        return (searchInternalRecursiveBST(pTreeNode->pLeftChild, key));
    } else {
        return (searchInternalRecursiveBST(pTreeNode->pRightChild, key));
    }
}

BinSearchTreeNode* searchBST(BinSearchTree* pBinSearchTree, int key) {
    BinSearchTreeNode* retNode;
    
    if (pBinSearchTree == NULL) {
        printf("pBinSearchTree ERROR\n");
        return (NULL);
    }
    retNode = pBinSearchTree->pRootNode;
    while (retNode) {
        if (retNode->key == key) {
            break ;
        } else if (retNode->key > key) {
            retNode = retNode->pLeftChild;
        } else {
            retNode = retNode->pRightChild;
        }
    }
    return (retNode);
}

void deleteBinSearchTree(BinSearchTree* pBinSearchTree) {
    if (pBinSearchTree == NULL) {
        printf("pBinSearchTree ERROR\n");
        return ;
    }
    if (pBinSearchTree->pRootNode == NULL) {
        printf("pRootNode ERROR\n");
        free(pBinSearchTree);
        return ;
    }
    deleteBinSearchTreeInternal(pBinSearchTree->pRootNode);
    free(pBinSearchTree);
}

void deleteBinSearchTreeInternal(BinSearchTreeNode* pTreeNode) {
    if (pTreeNode == NULL) {
        return ;
    }
    deleteBinSearchTreeInternal(pTreeNode->pLeftChild);
    deleteBinSearchTreeInternal(pTreeNode->pRightChild);
    free(pTreeNode);
}

void displayBinSearchTree(BinSearchTreeNode* pNode, int level, char type) {
    if (pNode != NULL) {
        printf("-[%d,%c] %d\n", level, type, pNode->key);
        displayBinSearchTree(pNode->pLeftChild, level + 1, 'L');
        displayBinSearchTree(pNode->pRightChild, level + 1, 'R');
    }
}

int main() {
    BinSearchTree* pBinSearchTree;
    BinSearchTree* pBinSearchTree2;
    BinSearchTreeNode pNode;
    BinSearchTreeNode* searchNode;

    pBinSearchTree = createBinSearchTree();
    // pBinSearchTree2 = createBinSearchTree();
    pNode.key = 30;
    pNode.value = 'a';
    pNode.pLeftChild = NULL;
    pNode.pRightChild = NULL;
    insertElementBST(pBinSearchTree, pNode);
    pNode.key = 20;
    pNode.value = 'b';
    pNode.pLeftChild = NULL;
    pNode.pRightChild = NULL;
    insertElementBST(pBinSearchTree, pNode);
    pNode.key = 40;
    pNode.value = 'c';
    pNode.pLeftChild = NULL;
    pNode.pRightChild = NULL;
    insertElementBST(pBinSearchTree, pNode);
    pNode.key = 10;
    pNode.value = 'd';
    pNode.pLeftChild = NULL;
    pNode.pRightChild = NULL;
    insertElementBST(pBinSearchTree, pNode);
    pNode.key = 24;
    pNode.value = 'e';
    pNode.pLeftChild = NULL;
    pNode.pRightChild = NULL;
    insertElementBST(pBinSearchTree, pNode);
    pNode.key = 34;
    pNode.value = 'f';
    pNode.pLeftChild = NULL;
    pNode.pRightChild = NULL;
    insertElementBST(pBinSearchTree, pNode);
    pNode.key = 46;
    pNode.value = 'g';
    pNode.pLeftChild = NULL;
    pNode.pRightChild = NULL;
    insertElementBST(pBinSearchTree, pNode);
    pNode.key = 6;
    pNode.value = 'h';
    pNode.pLeftChild = NULL;
    pNode.pRightChild = NULL;
    insertElementBST(pBinSearchTree, pNode);
    pNode.key = 14;
    pNode.value = 'i';
    pNode.pLeftChild = NULL;
    pNode.pRightChild = NULL;
    insertElementBST(pBinSearchTree, pNode);
    pNode.key = 22;
    pNode.value = 'j';
    pNode.pLeftChild = NULL;
    pNode.pRightChild = NULL;
    insertElementBST(pBinSearchTree, pNode);
    // pNode.key = 30;
    // pNode.value = 'a';
    // pNode.pLeftChild = NULL;
    // pNode.pRightChild = NULL;
    // insertRecursiveElementBST(pBinSearchTree2, pNode);
    // pNode.key = 20;
    // pNode.value = 'b';
    // pNode.pLeftChild = NULL;
    // pNode.pRightChild = NULL;
    // insertRecursiveElementBST(pBinSearchTree2, pNode);
    // pNode.key = 40;
    // pNode.value = 'c';
    // pNode.pLeftChild = NULL;
    // pNode.pRightChild = NULL;
    // insertRecursiveElementBST(pBinSearchTree2, pNode);
    // pNode.key = 10;
    // pNode.value = 'd';
    // pNode.pLeftChild = NULL;
    // pNode.pRightChild = NULL;
    // insertRecursiveElementBST(pBinSearchTree2, pNode);
    // pNode.key = 24;
    // pNode.value = 'e';
    // pNode.pLeftChild = NULL;
    // pNode.pRightChild = NULL;
    // insertRecursiveElementBST(pBinSearchTree2, pNode);
    // pNode.key = 34;
    // pNode.value = 'f';
    // pNode.pLeftChild = NULL;
    // pNode.pRightChild = NULL;
    // insertRecursiveElementBST(pBinSearchTree2, pNode);
    // pNode.key = 46;
    // pNode.value = 'g';
    // pNode.pLeftChild = NULL;
    // pNode.pRightChild = NULL;
    // insertRecursiveElementBST(pBinSearchTree2, pNode);
    // pNode.key = 6;
    // pNode.value = 'h';
    // pNode.pLeftChild = NULL;
    // pNode.pRightChild = NULL;
    // insertRecursiveElementBST(pBinSearchTree2, pNode);
    // pNode.key = 14;
    // pNode.value = 'i';
    // pNode.pLeftChild = NULL;
    // pNode.pRightChild = NULL;
    // insertRecursiveElementBST(pBinSearchTree2, pNode);
    // pNode.key = 22;
    // pNode.value = 'j';
    // pNode.pLeftChild = NULL;
    // pNode.pRightChild = NULL;
    // insertRecursiveElementBST(pBinSearchTree2, pNode);
    displayBinSearchTree(pBinSearchTree->pRootNode, 0, 'R');
    // printf("========================================================================\n");
    // displayBinSearchTree(pBinSearchTree2->pRootNode, 0, 'R');
    printf("============================deleteElementBST============================\n");
    // deleteElementBST(pBinSearchTree, 40);
    // displayBinSearchTree(pBinSearchTree->pRootNode, 0, 'R');
    deleteRecursiveElementBST(pBinSearchTree, 40);
    displayBinSearchTree(pBinSearchTree->pRootNode, 0, 'R');
    searchNode = searchRecursiveBST(pBinSearchTree, 22);
    printf("Recursive search => %d, %c\n", searchNode->key, searchNode->value);
    searchNode = searchBST(pBinSearchTree, 22);
    printf("Search => %d, %c\n", searchNode->key, searchNode->value);
    deleteBinSearchTree(pBinSearchTree);
    // deleteBinSearchTree(pBinSearchTree2);
}