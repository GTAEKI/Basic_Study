#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "ListBaseStack.h" // 스택을 위한 헤더 파일
#include "BinaryTree2.h"   // 이진 트리를 위한 헤더 파일

// 수식 문자열을 이용하여 수식 트리를 생성하는 함수
BTreeNode * MakeExpTree(char exp[])
{
    Stack stack;            // 스택 선언
    BTreeNode * pnode;      // 트리 노드를 가리키는 포인터

    int expLen = strlen(exp);   // 수식 문자열의 길이 계산
    int i;

    StackInit(&stack);      // 스택 초기화

    for(i = 0; i < expLen; i++)
    {
        pnode = MakeBTreeNode();    // 트리 노드 생성

        if(isdigit(exp[i]))     // 숫자인 경우
        {
            SetData(pnode, exp[i]-'0'); // 노드에 데이터 설정
        }
        else    // 연산자인 경우
        {
            // 오른쪽 서브 트리와 왼쪽 서브 트리 생성 및 연결
            MakeRightSubTree(pnode, SPop(&stack));
            MakeLeftSubTree(pnode, SPop(&stack));
            SetData(pnode, exp[i]); // 노드에 연산자 데이터 설정
        }

        SPush(&stack, pnode);   // 스택에 노드 추가
    }
    return SPop(&stack);    // 최종적으로 남은 루트 노드 반환
}

// 수식 트리를 계산하는 함수
int EvaluateExpTree(BTreeNode * bt)
{
    int op1, op2;

    if(GetLeftSubTree(bt) == NULL && GetRightSubTree(bt) == NULL) return GetData(bt); // 리프 노드인 경우 해당 노드의 데이터 반환

    // 왼쪽 서브 트리와 오른쪽 서브 트리의 계산 결과 얻기
    op1 = EvaluateExpTree(GetLeftSubTree(bt));
    op2 = EvaluateExpTree(GetRightSubTree(bt));

    switch (GetData(bt)) // 연산자에 따른 연산 수행
    {
    case '+':
        return op1 + op2;
        break;
    case '-':
        return op1 - op2;
        break;
    case '*':
        return op1 * op2;
        break;
    case '/':
        return op1 / op2;
        break;
    }

    return 0;
}

// 노드의 데이터 출력 함수
void ShowNodeData(int data)
{
    if(0 <= data && data <= 9) printf("%d ", data); // 숫자인 경우 숫자 출력
    else printf("%c ", data); // 연산자인 경우 연산자 출력
}

// 전위 표기 수식 출력 함수
void ShowPrefixTypeExp(BTreeNode * bt)
{
    PreorderTraverse(bt, ShowNodeData); // 전위 순회 수행
}

// 중위 표기 수식 출력 함수
void ShowInfixTypeExp(BTreeNode * bt)
{
    if(bt == NULL) return;

    if(bt->left != NULL || bt->right != NULL) printf(" ( "); // 서브 트리가 있는 경우 괄호 출력

    ShowInfixTypeExp(bt->left); // 왼쪽 서브 트리 순회
    ShowNodeData(bt->data); // 현재 노드 데이터 출력
    ShowInfixTypeExp(bt->right); // 오른쪽 서브 트리 순회

    if(bt->left != NULL || bt->right != NULL) printf(" ) "); // 서브 트리가 있는 경우 괄호 출력
}

// 후위 표기 수식 출력 함수
void ShowPostfixTypeExp(BTreeNode * bt)
{
    PostorderTraverse(bt, ShowNodeData); // 후위 순회 수행
}
