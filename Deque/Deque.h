#ifndef __DEQUE_H__
#define __DEQUE_H__

#define TRUE 1
#define FALSE 0

typedef int Data;

typedef struct _node
{
    Data data;
    struct _node * next;
    struct _node * prev;
} Node;

typedef struct _dlDeque
{
    Node * head;
    Node * tail;
} DLDeque;

typedef DLDeque Deque;

void DequeInit(Deque * pdeq);
int DQIsEmpty(Deque * pdeq);

void DQAddFirst(Deque * pdeq, Data data); // 덱의 머리에 데이터 추가
void DQAddLast(Deque * pdeq, Data data); // 덱의 미지막에 데이터 추가

Data DQRemoveFirst(Deque * pdeq); // 덱의 첫번째에서 데이터 삭제
Data DQRemoveLast(Deque * pdeq); // 덱의 꼬리에서 데이터 삭제

Data DQGetFirst(Deque * pdeq); // 덱의 머리의 데이터 확인
Data DQGetLast(Deque * pdeq); //덱의 꼬리의 데이터 확인

#endif