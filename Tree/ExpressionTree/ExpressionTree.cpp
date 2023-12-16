#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "ListBaseStack.h"
#include "BinaryTree2.h"

BTreeNode * MakeExpTree(char exp[])
{
    Stack stack;
    BTreeNode * pnode;

    int expLen = strlen(exp);
    int i;

    StackInit(&stack);

    for(i = 0; i<expLen; i++)
    {
        pnode = MakeBTreeNode();

        if(isdigit(exp[i]))
        {
            SetData(pnode, exp[i]-'0');
        }
        else
        {
            MakeRightSubTree(pnode, SPop(&stack));
            MakeLeftSubTree(pnode, SPop(&stack));
            SetData(pnode, exp[i]);
        }

        SPush(&stack, pnode);
    }
    return SPop(&stack);
}

int EvaluateExpTree(BTreeNode * bt)
{
    return 0;
}