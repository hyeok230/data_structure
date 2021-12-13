#include "bintree.h"
#include "bintreetraversal.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    BinTree* pBinTree;
    BinTreeNode rootNode;
    BinTreeNode element;

    rootNode.data = 'A';
    rootNode.pLeftChild = NULL;
    rootNode.pRightChild = NULL;
    pBinTree = makeBinTree(rootNode);
    element.data = 'B';
    element.pLeftChild = NULL;
    element.pRightChild = NULL;
    insertLeftChildNodeBT(pBinTree->pRootNode, element);
    element.data = 'C';
    element.pLeftChild = NULL;
    element.pRightChild = NULL;
    insertRightChildNodeBT(pBinTree->pRootNode, element);
    element.data = 'D';
    element.pLeftChild = NULL;
    element.pRightChild = NULL;
    insertLeftChildNodeBT(pBinTree->pRootNode->pLeftChild, element);
    element.data = 'E';
    element.pLeftChild = NULL;
    element.pRightChild = NULL;
    insertRightChildNodeBT(pBinTree->pRootNode->pLeftChild, element);
    element.data = 'F';
    element.pLeftChild = NULL;
    element.pRightChild = NULL;
    insertLeftChildNodeBT(pBinTree->pRootNode->pRightChild, element);
    element.data = 'G';
    element.pLeftChild = NULL;
    element.pRightChild = NULL;
    insertRightChildNodeBT(pBinTree->pRootNode->pRightChild, element);
    element.data = 'H';
    element.pLeftChild = NULL;
    element.pRightChild = NULL;
    insertLeftChildNodeBT(pBinTree->pRootNode->pLeftChild->pLeftChild, element);
    element.data = 'I';
    element.pLeftChild = NULL;
    element.pRightChild = NULL;
    insertRightChildNodeBT(pBinTree->pRootNode->pLeftChild->pLeftChild, element);
    element.data = 'J';
    element.pLeftChild = NULL;
    element.pRightChild = NULL;
    insertLeftChildNodeBT(pBinTree->pRootNode->pLeftChild->pRightChild, element);
    element.data = 'K';
    element.pLeftChild = NULL;
    element.pRightChild = NULL;
    insertRightChildNodeBT(pBinTree->pRootNode->pRightChild->pLeftChild, element);
    element.data = 'L';
    element.pLeftChild = NULL;
    element.pRightChild = NULL;
    insertLeftChildNodeBT(pBinTree->pRootNode->pRightChild->pRightChild, element);
    element.data = 'M';
    element.pLeftChild = NULL;
    element.pRightChild = NULL;
    insertRightChildNodeBT(pBinTree->pRootNode->pRightChild->pRightChild, element);
    printf("==========================preorder==========================\n");
    preorderBinTree(pBinTree);
    printf("==========================inorder==========================\n");
    inorderBinTree(pBinTree);
    printf("==========================postorder==========================\n");
    postorderBinTree(pBinTree);
    printf("==========================delete==========================\n");
    deleteBinTree(pBinTree);
}