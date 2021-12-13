#include "bintreetraversal.h"
#include <stdio.h>
#include <stdlib.h>

void preorderBinTree(BinTree* pBinTree) {
    if (pBinTree == NULL) {
        printf("PBinTree ERROR\n");
        return ;
    }
    preorderBinTreeNode(pBinTree->pRootNode);
}

void preorderBinTreeNode(BinTreeNode* pRootNode) {
    if (pRootNode == NULL) {
        return ;
    }
    printf("data -> [%c]\n", pRootNode->data);
    preorderBinTreeNode(pRootNode->pLeftChild);
    preorderBinTreeNode(pRootNode->pRightChild);
}

void inorderBinTree(BinTree* pBinTree) {
    if (pBinTree == NULL) {
        printf("PBinTree ERROR\n");
        return ;
    }
    inorderBinTreeNode(pBinTree->pRootNode);
}

void inorderBinTreeNode(BinTreeNode *pRootNode) {
    if (pRootNode == NULL) {
        return ;
    }
    inorderBinTreeNode(pRootNode->pLeftChild);
    printf("data -> [%c]\n", pRootNode->data);
    inorderBinTreeNode(pRootNode->pRightChild);
}

void postorderBinTree(BinTree *pBinTree) {
    if (pBinTree == NULL) {
        printf("PBinTree ERROR\n");
        return ;
    }
    postorderBinTreeNode(pBinTree->pRootNode);
}

void postorderBinTreeNode(BinTreeNode *pRootNode) {
    if (pRootNode == NULL) {
        return ;
    }
    postorderBinTreeNode(pRootNode->pLeftChild);
    postorderBinTreeNode(pRootNode->pRightChild);
    printf("data -> [%c]\n", pRootNode->data);
}