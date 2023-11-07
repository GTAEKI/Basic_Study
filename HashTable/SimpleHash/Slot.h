#ifndef __SLOT_H__
#define __SLOT_H__

#include "Person.h"

typedef int Key; //주민등록번호
typedef Person * Value; // Person 구조체 변수의 주소 값

enum SlotStatus {EMPTY, DELETED, INUSE}; // 슬롯의 상태를 나타내는 멤버
// EMPTY = 이 슬롯에는 데이터가 저장된바 없다.
// DELETED = 데이터가 저장된바 있으나 현재는 비워진 상태
// INUSE = 현재 유효한 데이터가 저장되어 있다.

typedef struct _slot 
{
    Key key;
    Value val;
    enum SlotStatus status;
} Slot;

#endif