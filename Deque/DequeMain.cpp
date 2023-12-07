#include<stdio.h>
#include"Deque.h"

Deque deq;

void InputData()
{
    DQAddFirst(&deq, 3);
    DQAddFirst(&deq, 2);
    DQAddFirst(&deq, 1);

    DQAddLast(&deq,4);
    DQAddLast(&deq,5);
    DQAddLast(&deq,6);
}

int main()
{
    //Deque 생성 및 초기화
    DequeInit(&deq);

    // 데이터 넣기 1차
    InputData();

    // 데이터 꺼내기 1차
    while(!DQIsEmpty(&deq))
    {
        printf("%d ", DQRemoveFirst(&deq));
    }

    printf("\n");

    // 데이터 넣기 2차
    InputData();

    // 데이터 꺼내기 2차
    while(!DQIsEmpty(&deq))
    {
        printf("%d ", DQRemoveLast(&deq));
    }

    return 0;

}