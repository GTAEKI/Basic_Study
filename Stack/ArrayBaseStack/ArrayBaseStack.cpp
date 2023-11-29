#include <stdio.h>
#include <stdlib.h>
#include "ArrayBaseStack.h"

void StackInit(Stack * pstack)
{
    pstack -> topIndex = -1;
}

int SIsEmpty(Stack * pstack)
{
    if(pstack -> topIndex == -1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void SPush(Stack * pstack, Data data)
{
    pstack -> topIndex += 1;
    pstack -> stackArr[pstack->topIndex] = data;
}

Data SPop(Stack * pstack)
{
    // 내가 임시로 작성
    // Data temp = 0;
    // temp = pstack -> stackArr[pstack->topIndex];
    // pstack -> stackArr[pstack->topIndex] = 0;
    // pstack -> topIndex -= 1;
    // return temp;

    int rIdx;

    if(SIsEmpty(pstack))
    {
        printf("Stack Memory Error!");
        exit(-1);
    }

    rIdx = pstack -> topIndex;
    pstack -> topIndex -= 1;

    return pstack -> stackArr[rIdx];
}

Data Speec(Stack * pstack)
{
    if(SIsEmpty(pstack))
    {
        printf("Stack Memory Error!");
        exit(-1);
    }

    return pstack -> stackArr[pstack->topIndex];
}