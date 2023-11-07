#include <stdio.h>
#include <stdlib.h>
#include "Person.h"
#include "Table2.h"

int MyHashFunc(int k)
{
    return k % 100;
}

int main(void)
{
    Table myTb1;
    Person * np;
    Person * sp;
    Person * rp;

    TBLInit(&myTb1, MyHashFunc);

    // 데이터 입력
    np = MakePersonData(900254, "Lee", "Seoul");
    TBLInsert(&myTb1, GetSSN(np), np);

    np = MakePersonData(900139, "Kim", "Jeju");
    TBLInsert(&myTb1, GetSSN(np), np);

    np = MakePersonData(900827, "HAN", "Kangwon");
    TBLInsert(&myTb1, GetSSN(np), np);

    // 데이터 탐색
    sp = TBLSearch(&myTb1, 900254);
    if(sp != NULL) ShowPerInfo(sp);

    sp = TBLSearch(&myTb1, 900139);
    if(sp != NULL) ShowPerInfo(sp);

    sp = TBLSearch(&myTb1, 900827);
    if(sp != NULL) ShowPerInfo(sp);

    // 데이터 삭제
    rp = TBLDelete(&myTb1, 900254);
    if(rp != NULL) free(rp);

    rp = TBLDelete(&myTb1, 900139);
    if(rp != NULL) free(rp);

    rp = TBLDelete(&myTb1, 900827);
    if(rp != NULL) free(rp);

    return 0;

}