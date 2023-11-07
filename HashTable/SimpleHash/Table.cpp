#include <stdio.h>
#include <stdlib.h>
#include "Table.h"

void TBLInit(Table * pt, HashFunc * f)
{
    int i;

    // 모든 슬롯 초기화
    for(i=0; i<MAX_TBL; i++)
    {
        (pt->tb1[i]).status = EMPTY;
    }

    pt->hf = f; //해쉬 함수 등록
}

void TBLInsert(Table * pt, Key k, Value v)
{
    int hv = pt -> hf(k);
    pt->tb1[hv].val = v;
    pt->tb1[hv].key = k;
    pt->tb1[hv].status = INUSE;
}

Value TBLDelete(Table * pt, Key k)
{
    int hv = pt->hf(k);
    
    if((pt->tb1[hv]).status != INUSE)
    {
        return NULL;
    }
    else
    {
        (pt->tb1[hv]).status = DELETED;
        return (pt->tb1[hv].val);
    }
}

Value TBLSearch(Table * pt, Key k)
{
    int hv = pt->hf(k);

    if((pt->tb1[hv]).status != INUSE)
    {
        return NULL;
    }
    else
    {
        return (pt->tb1[hv]).val;
    }
}