#ifndef __SIMPLE_HEAP_H__
#define __SIMPLE_HEAP_H__

#define TRUE 1
#define FALSE 0

#define HEAP_LEN 100 // 배열을 기반으로 한 힙을 구현하는 중

typedef char HData;
typedef int Priority;

typedef struct _heapElem
{
    Priority pr; //값이 작을수록 높은 우선순위 >> 우선순위 큐의 구현을 위한 우선순위이다.
    HData data;
} HeapElem;

typedef struct _heap
{
    int numOfData;
    HeapElem heapArr[HEAP_LEN];
} Heap;

void HeapInit(Heap * ph); // 힙 초기화
int HIsEmpty(Heap * ph); // 힙이 비어있는지 체크

void HInsert(Heap * ph, HData data, Priority pr); // 힙에 삽입
HData HDelete(Heap * ph); // 힙 제거

#endif