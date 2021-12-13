#include "bintree.h"
#include <stdio.h>
#include <stdlib.h>

BinTree* makeBinTree(BinTreeNode rootNode) {
    BinTree* pBinTree;
    
    pBinTree = (BinTree*)malloc(sizeof(BinTree));
    if (pBinTree == NULL) {
        printf("malloc ERROR\n");
        return (NULL);
    }
    pBinTree->pRootNode = (BinTreeNode*)malloc(sizeof(BinTreeNode));
    if (pBinTree->pRootNode == NULL) {
        printf("malloc ERROR\n");
        return (NULL);
    }
    *(pBinTree->pRootNode) = rootNode;
    pBinTree->pRootNode->pLeftChild = NULL;
    pBinTree->pRootNode->pRightChild = NULL;
    return (pBinTree);
}

BinTreeNode* getRootNodeBT(BinTree* pBinTree) {
    if (pBinTree == NULL) {
        printf("pBinTree ERROR\n");
        return (NULL);
    }
    if (pBinTree->pRootNode == NULL) {
        printf("RootNode ERROR\n");
        return (NULL);
    }
    return (pBinTree->pRootNode);
}

BinTreeNode* insertLeftChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element) {
    if (pParentNode == NULL) {
        printf("pParentNode ERROR\n");
        return (NULL);
    }
    pParentNode->pLeftChild = (BinTreeNode*)malloc(sizeof(BinTreeNode));
    if (pParentNode->pLeftChild == NULL) {
        printf("pParentNode LeftChild malloc ERROR\n");
        return (NULL);
    }
    *(pParentNode->pLeftChild) = element;
    pParentNode->pLeftChild->pLeftChild = NULL;
    pParentNode->pLeftChild->pRightChild = NULL;
    return (pParentNode->pLeftChild);
}

BinTreeNode* insertRightChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element) {
    if (pParentNode == NULL) {
        printf("pParentNode ERROR\n");
        return (NULL);
    }
    pParentNode->pRightChild = (BinTreeNode*)malloc(sizeof(BinTreeNode));
    if (pParentNode->pRightChild == NULL) {
        printf("pParentNode RightChild malloc ERROR\n");
        return (NULL);
    }
    *(pParentNode->pRightChild) = element;
    pParentNode->pRightChild->pLeftChild = NULL;
    pParentNode->pRightChild->pRightChild = NULL;
    return (pParentNode->pRightChild);
}

BinTreeNode* getLeftChildNodeBT(BinTreeNode* pNode) {
    if (pNode == NULL) {
        printf("pNode ERROR\n");
        return (NULL);
    }
    return (pNode->pLeftChild);
}

BinTreeNode* getRightChildNodeBT(BinTreeNode* pNode) {
    if (pNode == NULL) {
        printf("pNode ERROR\n");
        return (NULL);
    }
    return (pNode->pRightChild);
}

void deleteBinTree(BinTree* pBinTree) {
    if (pBinTree == NULL) {
        printf("pBinTree ERROR\n");
        return ;
    }
    deleteBinTreeNode(pBinTree->pRootNode);
    free(pBinTree);
}

void deleteBinTreeNode(BinTreeNode* pNode) {
    if (pNode == NULL) {
        printf("pNode ERROR\n");
        return ;
    }
    free(pNode->pLeftChild);
    free(pNode->pRightChild);
    free(pNode);
}