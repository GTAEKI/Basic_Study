// 이진트리 2번째는 순회의 과정에서 출력만을 위한것이 아닌 다른 일을 할 수 있도록 구현하는것이다.
// 때문에 VisitFuncPtr 함수 포인터를 정의하여 순회시 action을 지정해준다.

#ifndef __BINARY_TREE2_H__
#define __BINARY_TREE2_H__

typedef int BTData;

typedef struct _bTreeNode
{
    BTData data;
    struct _bTreeNode * left;
    struct _bTreeNode * right;
} BTreeNode;

BTreeNode * MakeBTreeNode(void);
BTData GetData(BTreeNode * bt);
void SetData(BTreeNode * bt, BTData data);

BTreeNode * GetLeftSubTree(BTreeNode * bt);
BTreeNode * GetRightSubTree(BTreeNode * bt);

void MakeLeftSubTree(BTreeNode * main, BTreeNode * sub);
void MakeRightSubTree(BTreeNode * main, BTreeNode * sub);

typedef void (*VisitFuncPtr)(BTData data); // 함수 포인터 정의

void PreorderTraverse(BTreeNode * bt, VisitFuncPtr action); // 후위 순회
void InorderTraverse(BTreeNode * bt, VisitFuncPtr action); // 중위 순회
void PostorderTraverse(BTreeNode * bt, VisitFuncPtr action); // 후위 순회

void DeleteTree(BTreeNode * bt);

#endif