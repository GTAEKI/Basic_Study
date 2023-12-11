#include<stdio.h>
#include<stdlib.h>
#include"BinaryTree.h"

// 중위 순회 구현
void InorderTraverse(BTreeNode * bt)
{
    if(bt == NULL) return; // 이진트리가 NULL일경우 재귀 탈출

    InorderTraverse(bt->left); // 중위 순회이므로 왼쪽 노드를 먼저 순회함
    printf("%d \n", bt->data); // 중간 노드 순회
    InorderTraverse(bt->right); // 마지막 오른쪽 노드 순회
}

// 후위순회 구현
void PostorderTraverse(BTreeNode * bt)
{
    if(bt == NULL) return;

    PostorderTraverse(bt->left);
    PostorderTraverse(bt->right);
    printf("%d \n",bt->data);
}

// 전위순회 구현
void PreorderTraverse(BTreeNode * bt)
{
    if(bt == NULL) return;

    printf("%d \n",bt->data);
    PreorderTraverse(bt->left);
    PreorderTraverse(bt->right);
}


int main()
{
    BTreeNode * bt1 = MakeBTreeNode(); //노드 bt1 생성
    BTreeNode * bt2 = MakeBTreeNode(); //노드 bt2 생성
    BTreeNode * bt3 = MakeBTreeNode(); //노드 bt3 생성
    BTreeNode * bt4 = MakeBTreeNode(); //노드 bt4 생성

    SetData(bt1, 1); //bt1에 1 저장
    SetData(bt2, 2); //bt2에 2 저장
    SetData(bt3, 3); //bt3에 3 저장
    SetData(bt4, 4); //bt4에 4 저장

    MakeLeftSubTree(bt1,bt2); //bt2를 bt1의 왼쪽 자식 노드로
    MakeRightSubTree(bt1,bt3); //bt3를 bt1의 오른쪽 자식 노드로
    MakeLeftSubTree(bt2,bt4); //bt4를 bt2의 왼쪽 자식 노드로

    InorderTraverse(bt1); // 중위 순회
    printf("\n");
    PostorderTraverse(bt1); //전위 순회
    printf("\n");
    PreorderTraverse(bt1); // 후위 순회
    return 0;
}