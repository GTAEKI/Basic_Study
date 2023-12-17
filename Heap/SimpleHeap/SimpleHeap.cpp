#include "SimpleHeap.h"

void HeapInit(Heap * ph)
{
    ph->numOfData = 0;
}

int HIsEmpty(Heap * ph)
{
    if(ph->numOfData == 0)
    {
        return TRUE;
    }
    else return FALSE;
}

int GetParentIDX(int idx) // 부모 노드의 인덱스 값 반환
{
    return idx/2;
}

int GetLChildIDX(int idx) // 왼쪽 자식 노드의 인덱스 값 반환
{
    return idx *2;
}

int GetRChildIDX(int idx) // 오른쪽 자식 노드의 인덱스 값 반환
{
    return GetLChildIDX(idx) +1;
}

// 두 개의 자식 노드 중 높은 우선순위에 있는 자식 노드의 인덱스 값을 반환
int GetHiPriChildIDX(Heap * ph, int idx)
{
    if(GetLChildIDX(idx) > ph -> numOfData) return 0;
    else if(GetLChildIDX(idx) == ph->numOfData) return GetLChildIDX(idx);
    else 
    {
        if(ph->heapArr[GetLChildIDX(idx)].pr > ph->heapArr[GetRChildIDX(idx)].pr) return GetRChildIDX(idx);
        else return GetLChildIDX(idx);
    }
}

void HInsert(Heap * ph, HData data, Priority pr)
{
    int idx = ph->numOfData +1;
    HeapElem nelem = {pr,data};

    while(idx != 1)
    {
        if(pr < (ph -> heapArr[GetParentIDX(idx)].pr))
        {
            ph -> heapArr[idx] = ph->heapArr[GetParentIDX(idx)];
            idx = GetParentIDX(idx);
        }
        else break;
    }

    ph->heapArr[idx] = nelem;
    ph->numOfData += 1;
}

// 힙 에서의 데이터 삭제
HData HDelete(Heap * ph)
{
    HData retData = (ph->heapArr[1]).data; // 반환을 위해 삭제할 데이터를 저장
    HeapElem lastElem = ph->heapArr[ph->numOfData]; // 힙의 마지막 노드 저장

    int parentIdx = 1; // 루트 노드가 위치해야할 인덱스 값 저장
    int childIdx;

// 루트 노드의 우선순위가 높은 자식 노드를 시작으로 반복문 시작
    while(childIdx = GetHiPriChildIDX(ph, parentIdx))
    {
        if(lastElem.pr <= ph->heapArr[childIdx].pr) break; // 마지막 노드와 우선순위를 비교함
        ph->heapArr[parentIdx] = ph->heapArr[childIdx]; // 마지막 노드보다 우선순위가 높으므로, 비교대상 노드의 위치를 한 레벨 올림
        parentIdx = childIdx; // 마지막 노드가 저장될 위치정보를 하나 내림
    } // 반복문 탈출 시점에서는 parentIdx에는 마지막 노드의 위치정보가 저장된다.

    ph->heapArr[parentIdx] = lastElem; // 마지막 노드 최종 저장
    ph->numOfData -= 1;
    return retData;
}