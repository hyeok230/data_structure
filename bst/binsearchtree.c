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

int deleteElementBST(BinSearchTree* pBinSearchTree, int key) {
    
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
    BinSearchTreeNode pNode;

    pBinSearchTree = createBinSearchTree();
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
    displayBinSearchTree(pBinSearchTree->pRootNode, 0, 'R');
    printf("============================deleteElementBST============================\n");
    // deleteElementBST(pBinSearchTree, 40);
    // displayBinSearchTree(pBinSearchTree->pRootNode, 0, 'R');

    deleteBinSearchTree(pBinSearchTree);
}