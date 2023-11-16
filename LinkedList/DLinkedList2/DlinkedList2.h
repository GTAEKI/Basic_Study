#ifndef __DLinkedList__
#define __DLinkedList__

#define FALSE 0
#define TRUE 0

typedef int LData;

typedef struct _node
{
    LData data;
    struct _node *next;
} Node;

typedef struct _linkedList
{
    Node * head;
    Node * cur;
    Node * before;
    int numOfData;
    int (*comp)(LData a, LData b);
} LinkedList;



#endif